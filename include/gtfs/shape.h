#pragma once

#include <ostream>

#include "gtfs/csv_parser.h"


namespace gtfs {
  class shape {
    public:
      static csv_parser<shape> parser;
      static std::string file_name;

      // Unique identifier for a shape
      std::string id;
      // Latitude of this point in the shape
      double latitude;
      // Longitude of this point in the shape
      double longitude;
      // Index of this point in the sequence of points for the shape
      int index;
      // Distance traveled from the previous shape point to get to this point
      double distance;

      shape() = default;


      // Standard stream output
      friend std::ostream& operator<<(std::ostream& os, const shape& s) {
        return os << "shape: \n"
          << "\tID: " << s.id << "\n"
          << "\tLat/Lon: " << s.latitude << "/" << s.longitude << "\n"
          << "\tPoint Index: " << s.index << "\n"
          << "\tDistance: " << s.distance << "\n";
      };
  };

  std::string shape::file_name = "shapes.txt";
  csv_parser<shape> shape::parser = {{
    { "shape_id",            make_field_mapper(&shape::id)         },
    { "shape_pt_lat",        make_field_mapper(&shape::latitude)   },
    { "shape_pt_lon",        make_field_mapper(&shape::longitude)  },
    { "shape_pt_sequence",   make_field_mapper(&shape::index)      },
    { "shape_dist_traveled", make_field_mapper(&shape::distance)   }
  }};
}
