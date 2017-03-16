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
    using header_list_t = std::vector<std::string>;


    std::string file_path;
    type_map_t field_types;

    std::ifstream input;
    header_list_t headers;


    public:
      csv_parser() = default;
      csv_parser(std::string file, type_map_t type_map) {
        this->file_path   = file;
        this->field_types = type_map;
      };

      void initialize() {
        this->input.clear();
        this->input.close();
        this->input.open(this->file_path);
        this->headers = _parse_headers();
      }

      object_list_t all() {
        object_list_t list;
        initialize();
        std::string row;
        while(std::getline(this->input, row)) list.push_back(_parse_line(row));
        finish();
        return list;
      };


      inline bool has_next() { return this->input.peek() != EOF; }

      value_type next() {
        std::string row;
        std::getline(this->input, row);
        return _parse_line(row);
      };

      inline void finish() { this->input.close(); }


    private:
      value_type _parse_line(std::string line) {
        value_type inst;
        auto columns = _tokenize_line(line);

        for(size_t index = 0; index < this->headers.size(); index++) {
          auto header = this->headers[index];
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

        return inst;
      };

      std::vector<std::string> _parse_headers() {
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
