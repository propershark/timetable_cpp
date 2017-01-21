#pragma once

#include <fstream>
#include <sstream>
#include <iterator>
#include <map>
#include <vector>

#include "gtfs/field_mapper.h"
#include "gtfs/types.h"

namespace gtfs {
  template<typename T>
  inline T get_column(std::istream& in) {
    std::string column;
    std::getline(in, column, ',');
    std::istringstream iss;
    T val;
    iss >> val;
    return val;
  };

  template<>
  inline double get_column<double>(std::istream& in) {
    std::string column;
    std::getline(in, column, ',');
    return std::stod(column);
  }

  template<>
  inline std::string get_column<std::string>(std::istream& in) {
    std::ostringstream column;

    // Quote-escaped columns need special parsing
    if(in.peek() == '"') {
      in.get();
      bool done = false;

      while(!done) {
        switch(in.peek()) {
          // If the next character is a quote, and the following character is a
          // comma or newline, the column is finished.
          // Otherwise, if the following character is another quote, it is
          // treated as a single quote character.
          // Any other following character would result in an invalid CSV.
          case '"':
            in.get();
            switch(in.peek()) {
              case '\n':
              case ',': done = true;
              case '"': in.get();
                        break;
              default:  break;
            }
            break;
          // For all other characters, input is continued.
          default:
            column << (char) in.get();
            break;
        }
      }
    } else {
      char next = in.get();
      // Consume until a delimiting character is found
      while(next != ',') {
        column << next;
        next = in.get();
      }
    }

    return column.str();
  };



  template<class T>
  class csv_parser {
    using value_type    = T;
    using object_list_t = std::vector<value_type>;
    using mapper_t      = field_mapper<value_type>;
    using type_map_t    = std::map<std::string, mapper_t>;


    std::string file = T::file_name;
    type_map_t field_types;
    std::ifstream input;


    public:
      csv_parser() = default;
      csv_parser(type_map_t type_map) {
        this->field_types = type_map;
      };

      object_list_t parse(std::string directory) {
        this->input = std::ifstream(directory + "/" + this->file);
        auto headers = _get_column_headers();

        std::string line;
        while(std::getline(this->input, line)) {
          std::stringstream iss(line);
          value_type inst;
          for(auto header : headers) {
            auto mapper = field_types[header];
            switch(mapper.type) {
              case tBOOL:   mapper.apply(inst, get_column<bool>(iss));        break;
              case tSTRING: mapper.apply(inst, get_column<std::string>(iss)); break;
              case tDOUBLE: mapper.apply(inst, get_column<double>(iss));      break;
              default:
              case tINT:    mapper.apply(inst, get_column<int>(iss));         break;
            }
          }
          std::cout << inst << "\n";
        }

        return object_list_t();
      };


    private:
      std::vector<std::string> _get_column_headers() {
        std::vector<std::string> columns;
        std::string header_line;
        std::getline(this->input, header_line);

        std::istringstream header_stream(header_line);
        std::string column;
        while(std::getline(header_stream, column, ','))
          columns.push_back(column);

        return columns;
      };
  };
}
