#pragma once

#include <ostream>

#include "gtfs/csv_parser.h"


namespace gtfs {
  class calendar {
    public:
      static csv_parser<calendar> parser;
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
          << "\tStart Date: " << c.start_date << "\n"
          << "\tEnd Date: " << c.end_date << "\n";
      };
  };

  std::string calendar::file_name = "calendar.txt";
  csv_parser<calendar> calendar::parser = {{
    { "service_id",  make_field_mapper(&calendar::service_id)  },
    { "monday",      make_field_mapper(&calendar::monday)      },
    { "tuesday",     make_field_mapper(&calendar::tuesday)     },
    { "wednesday",   make_field_mapper(&calendar::wednesday)   },
    { "thursday",    make_field_mapper(&calendar::thursday)    },
    { "friday",      make_field_mapper(&calendar::friday)      },
    { "saturday",    make_field_mapper(&calendar::saturday)    },
    { "sunday",      make_field_mapper(&calendar::sunday)      },
    { "start_date",  make_field_mapper(&calendar::start_date)  },
    { "end_date",    make_field_mapper(&calendar::end_date)    }
  }};
}
