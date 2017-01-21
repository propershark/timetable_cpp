#pragma once

#include <ostream>

#include "gtfs/csv_parser.h"


namespace gtfs {
  class stop {

    public:
      static csv_parser<stop> parser;
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
      double latitude;
      // Longitude of this stop
      double longitude;
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
  csv_parser<stop> stop::parser = {{
    { "stop_id",             make_field_mapper(&stop::id)                  },
    { "stop_code",           make_field_mapper(&stop::code)                },
    { "stop_name",           make_field_mapper(&stop::name)                },
    { "stop_desc",           make_field_mapper(&stop::description)         },
    { "stop_lat",            make_field_mapper(&stop::latitude)            },
    { "stop_lon",            make_field_mapper(&stop::longitude)           },
    { "zone_id",             make_field_mapper(&stop::zone_id)             },
    { "stop_url",            make_field_mapper(&stop::stop_url)            },
    { "location_type",       make_field_mapper(&stop::type)                },
    { "parent_station",      make_field_mapper(&stop::parent_id)           },
    { "stop_timezone",       make_field_mapper(&stop::timezone)            },
    { "wheelchair_boarding", make_field_mapper(&stop::wheelchair_boarding) }
  }};
}
