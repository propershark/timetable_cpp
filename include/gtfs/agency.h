#pragma once

#include <ostream>

#include "gtfs/csv_parser.h"


namespace gtfs {
  class agency {
    static csv_parser<agency> parser;
    static type_map_t type_map;

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
  type_map_t agency::type_map = {
    {"agency_id",       type::t_string},
    {"agency_name",     type::t_string},
    {"agency_url",      type::t_string},
    {"agency_timezone", type::t_string},
    {"agency_lang",     type::t_string},
    {"agency_phone",    type::t_string},
    {"agency_fare_url", type::t_string},
    {"agency_email",    type::t_string}
  };
}
