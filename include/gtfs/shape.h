#pragma once

#include <ostream>


namespace gtfs {
  class shape {
    public:
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
}
