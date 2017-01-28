#pragma once

#include <ostream>

#include "gtfs/csv_parser.h"


namespace gtfs {
  class trip {
    public:
      static csv_parser<trip> parser;
      static std::string file_name;

      // Identifier of the route traveled by this trip
      std::string route_id;
      // Identifier of the service containing this trip
      std::string service_id;
      // Identifier of this trip
      std::string id;
      // Text displayed on vehicles traveling on this trip
      std::string headsign;
      // Short, humanized name for this trip
      std::string short_name;
      // Identifier of the direction traveled by this trip
      std::string direction_id;
      // Identifier of the block containing this trip
      std::string block_id;
      // Identifier of the shape traveled by this trip
      std::string shape_id;
      // Indication of wheelchair accessibility for this trip
      int wheelchair_accessible;
      // Indication of whether bikes are allowed for this trip
      int bikes_allowed;

      trip() = default;


      // Standard stream output
      friend std::ostream& operator<<(std::ostream& os, const trip& t) {
        return os << "trip: \n"
          << "\tRoute ID: " << t.route_id << "\n"
          << "\tService ID: " << t.service_id << "\n"
          << "\tID: " << t.id << "\n"
          << "\tHeadsign: " << t.headsign << "\n"
          << "\tShort Name: " << t.short_name << "\n"
          << "\tDirection ID: " << t.direction_id << "\n"
          << "\tBlock ID: " << t.block_id << "\n"
          << "\tShape ID: " << t.shape_id << "\n"
          << "\tWheelchair Accessibility: " << t.wheelchair_accessible << "\n"
          << "\tBikes Allowed: " << t.bikes_allowed << "\n";
      };
  };

  std::string trip::file_name = "trips.txt";
  csv_parser<trip> trip::parser = {{
    { "route_id",              make_field_mapper(&trip::route_id)              },
    { "service_id",            make_field_mapper(&trip::service_id)            },
    { "trip_id",               make_field_mapper(&trip::id)                    },
    { "trip_headsign",         make_field_mapper(&trip::headsign)              },
    { "trip_short_name",       make_field_mapper(&trip::short_name)            },
    { "direction_id",          make_field_mapper(&trip::direction_id)          },
    { "block_id",              make_field_mapper(&trip::block_id)              },
    { "shape_id",              make_field_mapper(&trip::shape_id)              },
    { "wheelchair_accessible", make_field_mapper(&trip::wheelchair_accessible) },
    { "bikes_allowed",         make_field_mapper(&trip::bikes_allowed)         }
  }};
}
