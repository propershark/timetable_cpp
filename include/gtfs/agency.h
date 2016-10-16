#pragma once

#include <ostream>

#include "gtfs/decls.h"


namespace GTFS {
  class Agency {
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

      Agency() = default;
      Agency(std::string id, std::string name, std::string url, std::string tz, std::string lang, std::string phone) : id(id), name(name), url(url), timezone(tz), language(lang), phone(phone) {};


      // Standard stream output
      friend std::ostream& operator<<(std::ostream& os, const Agency& a) {
        return os << "Agency: \n"
          << "\tID: " << a.id << "\n"
          << "\tName: " << a.name << "\n"
          << "\tURL: " << a.url << "\n"
          << "\tTZ: " << a.timezone << "\n"
          << "\tLang: " << a.language << "\n"
          << "\tPhone: " << a.phone << "\n";
      }
  };
}
