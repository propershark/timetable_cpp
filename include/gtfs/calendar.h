#pragma once

#include <ostream>


namespace gtfs {
  class calendar {
    public:
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

      void post_init() { };

      // Standard stream output
      friend std::ostream& operator<<(std::ostream& os, const calendar& c) {
        return os << "calendar: \n"
          << "\tService: " << c.service_id << "\n"
          << "\tMTWTFSS\n\t"
          << c.monday << c.tuesday << c.wednesday << c.thursday << c.friday << c.saturday << c.sunday << "\n"
          << "\tStart Date: " << c.start_date << "\n"
          << "\tEnd Date: " << c.end_date << "\n";
      };
  };
}
