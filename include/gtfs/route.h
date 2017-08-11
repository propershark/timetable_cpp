#pragma once

#include <ostream>


namespace gtfs {
  class route {
    public:
      // Unique identifier for the route
      std::string id;
      // Identifier of the Agency that owns the route
      std::string agency_id;
      // Short, humanized identifier of the route
      std::string short_name;
      // Fully-humanized name of the route
      std::string long_name;
      // Description of the route's service
      std::string description;
      // URL for a page containing information about the route
      std::string url;
      // Type of transportation used on the route
      int type;
      // Background color to use when displaying the route
      std::string color;
      // Text color to use when displaying the route
      std::string text_color;

      route() = default;

      void post_init() {
        if (short_name.empty()) short_name = id;
        if (description.empty()) description = long_name;
      }

      // Standard stream output
      friend std::ostream& operator<<(std::ostream& os, const route& r) {
        return os << "route: \n"
          << "\tID: " << r.id << "\n"
          << "\tAgency: " << r.agency_id << "\n"
          << "\tShort Name: " << r.short_name << "\n"
          << "\tName: " << r.long_name << "\n"
          << "\tDescription: " << r.description << "\n"
          << "\tColor: " << r.color << "\n"
          << "\tText Color: " << r.text_color << "\n";
      };
  };
}
