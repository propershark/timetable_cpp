#pragma once

#include <fstream>
#include <iterator>
#include <map>
#include <sstream>
#include <vector>

#include "gtfs/field_mapper.h"
#include "gtfs/types.h"

namespace gtfs {
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
          value_type inst;
          auto columns = _tokenize_line(line);

          for(size_t index = 0; index < headers.size(); index++) {
            auto header = headers[index];
            auto column = columns[index];
            auto mapper = field_types[header];

            switch(mapper.type) {
              case tBOOL:   mapper.apply(inst, column == "1");     break;
              case tDOUBLE: mapper.apply(inst, std::stod(column)); break;
              case tINT:    mapper.apply(inst, std::stoi(column)); break;
              case tSTRING: mapper.apply(inst, column);            break;
              default:      break;
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

      // Return the given line as a series of column tokens to be parsed and
      // applied by the field mapper for the column.
      std::vector<std::string> _tokenize_line(std::string line) {
        std::vector<std::string> tokens;
        size_t current         = 0;
        size_t token_start     = 0;

        while(current < line.size()) {
          // The loop iterates once per token. The parsing of the token is done
          // by the control branches inside of the loop.
          token_start = current;

          // If the first character is a quote, the token is "quote-escaped",
          // and is not finished until the quote is unescaped.
          if(line[current] == '"') {
            current++;
            // Unescaping the quote is done when a quote character is followed
            // by either a comma (normal delimiter) or a newline character.
            while(current < line.size() &&
                !(line[current] == '"' && (line[current+1] == ',' || line[current+1] == '\n')))
              current++;
            // Strip the quote characters from the ends of the token.
            // Ex: "hello" -> hello
            tokens.push_back(line.substr(token_start+1, current-1-token_start));
            // Iterate past the escape quote.
            current++;
          } else {
            while(current < line.size() && line[current] != ',') current++;
            tokens.push_back(line.substr(token_start, current-token_start));
          }
          current++;
        }

        return tokens;
      };
  };
}
