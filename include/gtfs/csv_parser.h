#pragma once

#include <map>
#include <vector>

namespace gtfs {
  enum class type {
    t_string,
    t_char,
    t_bool,
    t_int,
    t_float
  };

  struct field_mapping_t {};
  template<class Type, typename Value, Value Type::*member>
  struct field_mapping : field_mapping_t {
    Value set_value(Type& inst, Value value) {
      inst.*member = value;
      return value;
    };
  };

  using type_map_t = std::map<std::string, field_mapping_t>;

  template<class Class, typename Result, Result Class::*actual_field>
  constexpr auto make_field_mapping() {
    return field_mapping<Class, Result, actual_field>();
  };

  template<typename T>
  class csv_parser {
    using object_list_t = std::vector<T>;

    std::string file = T::file_name;
    type_map_t field_types;

    public:
      csv_parser() = default;
      csv_parser(type_map_t type_map) {
        this->field_types = type_map;
      };
  };
}
