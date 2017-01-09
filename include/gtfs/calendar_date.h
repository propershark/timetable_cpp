#pragma once

#include <ostream>

#include "gtfs/csv_parser.h"


namespace gtfs {
  class calendar_date {
    static csv_parser<calendar_date> parser;
    static type_map_t type_map;

    public:
      static std::string file_name;
      // Identifier for the service affected by this calendar date
      std::string service_id;
      // Date for which the service exception applies
      std::string date;
      // Code of the type of exception that will occur
      int exception_type;

      calendar_date() = default;


      // Standard stream output
      friend std::ostream& operator<<(std::ostream& os, const calendar_date& cd) {
        return os << "calendar_date: \n"
          << "\tService ID: " << cd.service_id << "\n"
          << "\tDate: " << cd.date << "\n"
          << "\tException Type: " << cd.exception_type << "\n";
      };
  };

  std::string calendar_date::file_name = "calendar_dates.txt";
  type_map_t calendar_date::type_map = {
    {"service_id", type::t_string},
    {"date", type::t_string},
    {"exception_type", type::t_int}
  };
}
