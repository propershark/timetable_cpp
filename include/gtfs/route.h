#pragma once

#include <ostream>

#include "gtfs/csv_parser.h"


namespace gtfs {
  class route {
    static csv_parser<route> parser;

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
  csv_parser<route> route::parser = {{
    { "route_id",         field_mapping<route, std::string, &route::id>()           },
    { "agency_id",        field_mapping<route, std::string, &route::agency_id>()    },
    { "route_short_name", field_mapping<route, std::string, &route::short_name>()   },
    { "route_long_name",  field_mapping<route, std::string, &route::long_name>()    },
    { "route_desc",       field_mapping<route, std::string, &route::description>()  },
    { "route_url",        field_mapping<route, std::string, &route::url>()          },
    { "route_type",       field_mapping<route, int,         &route::type>()         },
    { "route_color",      field_mapping<route, std::string, &route::color>()        },
    { "route_text_color", field_mapping<route, std::string, &route::text_color>()   }
  }};
}
