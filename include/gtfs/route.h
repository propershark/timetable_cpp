#pragma once

#include <ostream>

#include "gtfs/csv_parser.h"


namespace gtfs {
  class route {
    static csv_parser<route> parser;
    static type_map_t type_map;

    public:
      static std::string file_name;
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

  std::string route::file_name = "routes.txt";
  type_map_t route::type_map = {
    {"route_id", type::t_string},
    {"agency_id", type::t_string},
    {"route_short_name", type::t_string},
    {"route_long_name", type::t_string},
    {"route_desc", type::t_string},
    {"route_type", type::t_int},
    {"route_url",  type::t_string},
    {"route_color", type::t_string},
    {"route_text_color", type::t_string}
  };
}
