#pragma once

#include <ostream>

#include "gtfs/csv_parser.h"


namespace gtfs {
  class calendar {
    static csv_parser<calendar> parser;

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
          << "\tStart Date: " << c.start_date << "\n"
          << "\tEnd Date: " << c.end_date << "\n";
      };
  };

  std::string calendar::file_name = "calendar.txt";
  csv_parser<calendar> calendar::parser = {{
    { "service_id",  field_mapping<calendar, std::string, &calendar::service_id>()  },
    { "monday",      field_mapping<calendar, bool,        &calendar::monday>()      },
    { "tuesday",     field_mapping<calendar, bool,        &calendar::tuesday>()     },
    { "wednesday",   field_mapping<calendar, bool,        &calendar::wednesday>()   },
    { "thursday",    field_mapping<calendar, bool,        &calendar::thursday>()    },
    { "friday",      field_mapping<calendar, bool,        &calendar::friday>()      },
    { "saturday",    field_mapping<calendar, bool,        &calendar::saturday>()    },
    { "sunday",      field_mapping<calendar, bool,        &calendar::sunday>()      },
    { "start_date",  field_mapping<calendar, std::string, &calendar::start_date>()  },
    { "end_date",    field_mapping<calendar, std::string, &calendar::end_date>()    }
  }};
}
