#pragma once

#include <ostream>

#include "gtfs/decls.h"


namespace GTFS {
  class Stop : public ObjectBase<Stop, std::string, std::string, std::string, std::string, float, float, int> {
    public:
      static std::string table_name;
      // Unique identifier for the stop
      std::string id;
      // Code used on signs and displays to represent this stop
      std::string code;
      // Full name of the stop
      std::string name;
      // Description of what area the stop services
      std::string description;
      // Latitude of this stop
      float latitude;
      // Longitude of this stop
      float longitude;
      // Code for the kind of stop at this location
      int type;

      Stop() = default;
      Stop(std::string id, std::string code, std::string name, std::string desc, float lat, float lon, int type) : id(id), code(code), name(name), description(desc), latitude(lat), longitude(lon), type(type) {};


      // Standard stream output
      friend std::ostream& operator<<(std::ostream& os, const Stop& s) {
        return os << "Stop: \n"
          << "\tID: " << s.id << "\n"
          << "\t(Code) Name: (" << s.code << ") " << s.name << "\n"
          << "\tDescription: " << s.description << "\n"
          << "\tLat/Lon: " << s.latitude << "/" << s.longitude << "\n"
          << "\tType: " << s.type << "\n";
      };
  };

  std::string Stop::table_name = "stops";
}
