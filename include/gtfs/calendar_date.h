#pragma once

#include <ostream>

#include "gtfs/csv_parser.h"


namespace gtfs {
  class calendar_date {
    public:
      static csv_parser<calendar_date> parser;
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
  csv_parser<calendar_date> calendar_date::parser = {{
    { "service_id",     make_field_mapper(&calendar_date::service_id)     },
    { "date",           make_field_mapper(&calendar_date::date)           },
    { "exception_type", make_field_mapper(&calendar_date::exception_type) }
  }};
}
