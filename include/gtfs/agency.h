#pragma once

#include <ostream>


namespace gtfs {
  class agency {
    public:
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
}
