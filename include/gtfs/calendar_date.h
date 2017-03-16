#pragma once

#include <ostream>


namespace gtfs {
  class calendar_date {
    public:
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
}
