#pragma once

#include <ostream>

#include "gtfs/decls.h"


namespace GTFS {
  class Shape : public ObjectBase<Shape, std::string, float, float, int, float> {
    public:
      static std::string table_name;
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

      Shape() = default;
      Shape(std::string id, float lat, float lon, int idx, float dist) : id(id), latitude(lat), longitude(lon), index(idx), distance(dist) {};


      // Standard stream output
      friend std::ostream& operator<<(std::ostream& os, const Shape& s) {
        return os << "Shape: \n"
          << "\tID: " << s.id << "\n"
          << "\tLat/Lon: " << s.latitude << "/" << s.longitude << "\n"
          << "\tPoint Index: " << s.index << "\n"
          << "\tDistance: " << s.distance << "\n";
      };
  };

  std::string Shape::table_name = "shapes";
}
