#pragma once

#include <ostream>


namespace gtfs {
  class trip {
    public:
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

      void post_init() { };

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
}
