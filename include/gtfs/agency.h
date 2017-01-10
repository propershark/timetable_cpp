#pragma once

#include <ostream>

#include "gtfs/csv_parser.h"


namespace gtfs {
  class agency {
    static csv_parser<agency> parser;

    public:
      static std::string file_name;
      // Unique identifier for the agency
      std::string id;
      // Humanized name of the agency
      std::string name;
      // URL for the website of the agency
      std::string url;
      // Timezone designator string for the agency
      std::string timezone;
      // Language used by the agency
      std::string language;
      // Phone number for contacting the agency
      std::string phone;
      // URL for fare information for the agency
      std::string fare_url;
      // Email address for contacting the agency
      std::string email;

      agency() = default;


      // Standard stream output
      friend std::ostream& operator<<(std::ostream& os, const agency& a) {
        return os << "agency: \n"
          << "\tID: " << a.id << "\n"
          << "\tName: " << a.name << "\n"
          << "\tURL: " << a.url << "\n"
          << "\tTZ: " << a.timezone << "\n"
          << "\tLang: " << a.language << "\n"
          << "\tPhone: " << a.phone << "\n";
      };
  };

  std::string agency::file_name = "agency.txt";
  csv_parser<agency> agency::parser = {{
    { "agency_id",        field_mapping<agency, std::string, &agency::id>()       },
    { "agency_name",      field_mapping<agency, std::string, &agency::name>()     },
    { "agency_url",       field_mapping<agency, std::string, &agency::url>()      },
    { "agency_timezone",  field_mapping<agency, std::string, &agency::timezone>() },
    { "agency_lang",      field_mapping<agency, std::string, &agency::language>() },
    { "agency_phone",     field_mapping<agency, std::string, &agency::phone>()    },
    { "agency_fare_url",  field_mapping<agency, std::string, &agency::fare_url>() },
    { "agency_email",     field_mapping<agency, std::string, &agency::email>()    }
  }};
}
