#pragma once

#include <map>
#include <vector>

#include "minicsv.h"
#include "gtfs/types.h"

namespace gtfs {
  template<class Class>
  struct field_mapper {
    bool        Class::*bool_target;
    std::string Class::*string_target;
    int         Class::*int_target;
    float       Class::*float_target;
    Type        type;

    explicit field_mapper() = default;
    explicit field_mapper(bool         Class::*member) : bool_target(member),   type(BOOL)    {};
    explicit field_mapper(std::string  Class::*member) : string_target(member), type(STRING)  {};
    explicit field_mapper(int          Class::*member) : int_target(member),    type(INT)     {};
    explicit field_mapper(float        Class::*member) : float_target(member),  type(FLOAT)   {};

    inline void apply(Class& inst, bool val)        const { inst.*bool_target   = val; };
    inline void apply(Class& inst, std::string val) const { inst.*string_target = val; };
    inline void apply(Class& inst, int val)         const { inst.*int_target    = val; };
    inline void apply(Class& inst, float val)       const { inst.*float_target  = val; };
  };

  template<class Class, typename ValueType>
  constexpr auto make_field_mapper(ValueType Class::*member) {
    return field_mapper<Class>(member);
  };


  template<class T>
  class csv_parser {
    using value_type    = T;
    using object_list_t = std::vector<value_type>;
    using mapper_t      = field_mapper<value_type>;
    using type_map_t    = std::map<std::string, mapper_t>;


    std::string file = T::file_name;
    type_map_t field_types;


    public:
      csv_parser() = default;
      csv_parser(type_map_t type_map) {
        this->field_types = type_map;
      };

      object_list_t parse(std::string directory) {
        mini::csv::ifstream is((directory + "/" + this->file).c_str());
        is.enable_trim_quote_on_str(true, '\"');
        auto headers = _get_column_headers(is);

        while(is.read_line()) {
          value_type inst;
          for(auto header : headers) {
            auto mapper = field_types[header];
            bool b; std::string s; int i; float f;
            switch(mapper.type) {
              case BOOL:    is >> b; mapper.apply(inst, b); break;
              case STRING:  is >> s; mapper.apply(inst, s); break;
              case INT:     is >> i; mapper.apply(inst, i); break;
              case FLOAT:   is >> f; mapper.apply(inst, f); break;
            }
          }
          std::cout << inst << "\n";
        }

        return object_list_t();
      };


    private:
      std::vector<std::string> _get_column_headers(mini::csv::ifstream& is) {
        std::vector<std::string> columns;
        is.read_line();
        while(!is.get_rest_of_line().empty()) {
          std::string column_name;
          is >> column_name;
          columns.push_back(column_name);
        }

        return columns;
      };
  };
}
