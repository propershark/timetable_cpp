#pragma once

#include <ostream>

#include "gtfs/csv_parser.h"


namespace gtfs {
  class calendar {
    static csv_parser<calendar> parser;
    static type_map_t type_map;

    public:
      static std::string file_name;
      // Identifier for the service this calendar record affects.
      std::string service_id;
      // Indication of service on the given day.
      bool monday;
      bool tuesday;
      bool wednesday;
      bool thursday;
      bool friday;
      bool saturday;
      bool sunday;
      // First date that this record is in effect.
      std::string start_date;
      // Last date that this record is in effect.
      std::string end_date;

      calendar() = default;


      // Standard stream output
      friend std::ostream& operator<<(std::ostream& os, const calendar& c) {
        return os << "calendar: \n"
          << "\tService: " << c.service_id << "\n"
          << "\tMTWTFSS\n\t"
          << c.monday << c.tuesday << c.wednesday << c.thursday << c.friday << c.saturday << c.sunday << "\n"
          << "\Start Date: " << c.start_date << "\n"
          << "\tEnd Date: " << c.end_date << "\n";
      };
  };

  std::string calendar::file_name = "calendar.txt";
  type_map_t calendar::type_map = {
    {"service_id",  type::t_string},
    {"monday",      type::t_bool},
    {"tuesday",     type::t_bool},
    {"wednesday",   type::t_bool},
    {"thursday",    type::t_bool},
    {"friday",      type::t_bool},
    {"saturday",    type::t_bool},
    {"sunday",      type::t_bool},
    {"start_date",  type::t_string},
    {"end_date",    type::t_string}
  };
}
