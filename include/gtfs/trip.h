#pragma once

#include <ostream>

#include "gtfs/decls.h"


namespace GTFS {
  class Trip : public ObjectBase<Trip, std::string, std::string, std::string, std::string, std::string, std::string, std::string> {
    public:
      static std::string table_name;
      // Identifier of the route traveled by this trip
      std::string route_id;
      // Identifier of the service containing this trip
      std::string service_id;
      // Unique identifier for this trip
      std::string id;
      // Identifier of the shape traveled by this trip
      std::string shape_id;
      // Text displayed on vehicles traveling on this trip
      std::string headsign;
      // Identifier of the direction traveled by this trip
      std::string direction_id;
      // Identifier of the block containing this trip
      std::string block_id;

      Trip() = default;
      Trip(std::string rid, std::string sid, std::string id, std::string shid, std::string hs, std::string did, std::string bid) : route_id(rid), service_id(sid), id(id), shape_id(shid), headsign(hs), direction_id(did), block_id(bid) {};


      // Standard stream output
      friend std::ostream& operator<<(std::ostream& os, const Trip& s) {
        return os << "Trip: \n"
          << "\tID: " << s.id << "\n"
          << "\tRoute ID: " << s.route_id << "\n"
          << "\tService ID: " << s.service_id << "\n"
          << "\tShape ID: " << s.shape_id << "\n"
          << "\tDirection ID: " << s.direction_id << "\n"
          << "\tBlock ID: " << s.block_id << "\n"
          << "\tHeadsign: " << s.headsign << "\n";
      };
  };

  std::string Trip::table_name = "trips";
}
