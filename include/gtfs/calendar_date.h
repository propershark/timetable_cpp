#pragma once

#include <ostream>

#include "gtfs/decls.h"


namespace GTFS {
  class CalendarDate : public ObjectBase<CalendarDate, std::string, std::string, int> {
    public:
      static std::string table_name;
      // Identifier for the service affected by this calendar date
      std::string service_id;
      // Date for which the service exception applies
      std::string date;
      // Code of the type of exception that will occur
      int exception_type;

      CalendarDate() = default;
      CalendarDate(std::string sid, std::string date, int e_type) : service_id(sid), date(date), exception_type(e_type) {};


      // Standard stream output
      friend std::ostream& operator<<(std::ostream& os, const CalendarDate& cd) {
        return os << "CalendarDate: \n"
          << "\tService ID: " << cd.service_id << "\n"
          << "\tDate: " << cd.date << "\n"
          << "\tException Type: " << cd.exception_type << "\n";
      };
  };

  std::string CalendarDate::table_name = "calendar_dates";
}
