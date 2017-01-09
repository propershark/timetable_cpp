#pragma once

#include <ostream>

#include "gtfs/csv_parser.h"


namespace gtfs {
  class shape {
    static csv_parser<shape> parser;
    static type_map_t type_map;

    public:
      static std::string file_name;
      // Unique identifier for a shape
      std::string id;
      // Latitude of this point in the shape
      float latitude;
      // Longitude of this point in the shape
      float longitude;
      // Index of this point in the sequence of points for the shape
      int index;
      // Distance traveled from the previous shape point to get to this point
      float distance;

      shape() = default;
      shape(std::string id, float lat, float lon, int idx, float dist) : id(id), latitude(lat), longitude(lon), index(idx), distance(dist) {};


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
  type_map_t shape::type_map = {
    {"shape_id",            type::t_string},
    {"shape_pt_lat",        type::t_float},
    {"shape_pt_lon",        type::t_float},
    {"shape_pt_sequence",   type::t_int},
    {"shape_dist_traveled", type::t_float}
  };
}
