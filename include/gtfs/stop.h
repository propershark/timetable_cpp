#pragma once

#include <ostream>

#include "gtfs/csv_parser.h"


namespace gtfs {
  class stop {
    static csv_parser<stop> parser;
    static type_map_t type_map;

    public:
      static std::string file_name;
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
      // Identifier for the fare zone this stop is in
      std::string zone_id;
      // URL for more information about this stop
      std::string stop_url;
      // Code for the kind of stop at this location
      int type;
      // The "parent station" of this stop (often blank)
      std::string parent_id;
      // The timezone this stop is located in
      std::string timezone;
      // Indication of whether wheelchair users can board at this station
      int wheelchair_boarding;

      stop() = default;
      stop(std::string id, std::string code, std::string name, std::string desc, float lat, float lon, int type) : id(id), code(code), name(name), description(desc), latitude(lat), longitude(lon), type(type) {};


      // Standard stream output
      friend std::ostream& operator<<(std::ostream& os, const stop& s) {
        return os << "stop: \n"
          << "\tID: " << s.id << "\n"
          << "\t(Code) Name: (" << s.code << ") " << s.name << "\n"
          << "\tDescription: " << s.description << "\n"
          << "\tLat/Lon: " << s.latitude << "/" << s.longitude << "\n"
          << "\tType: " << s.type << "\n";
      };
  };

  std::string stop::file_name = "stops.txt";
  type_map_t stop::type_map = {
    {"stop_id",             type::t_string},
    {"stop_code",           type::t_string},
    {"stop_name",           type::t_string},
    {"stop_desc",           type::t_string},
    {"stop_lat",            type::t_float},
    {"stop_lon",            type::t_float},
    {"zone_id",             type::t_string},
    {"stop_url",            type::t_string},
    {"location_type",       type::t_int},
    {"parent_station",      type::t_string},
    {"stop_timezone",       type::t_string},
    {"wheelchair_boarding", type::t_int}
  };
}
