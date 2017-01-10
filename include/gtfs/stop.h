#pragma once

#include <ostream>

#include "gtfs/csv_parser.h"


namespace gtfs {
  class stop {
    static csv_parser<stop> parser;

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
    { "stop_id",             field_mapping<stop, std::string, &stop::id>()                  },
    { "stop_code",           field_mapping<stop, std::string, &stop::code>()                },
    { "stop_name",           field_mapping<stop, std::string, &stop::name>()                },
    { "stop_desc",           field_mapping<stop, std::string, &stop::description>()         },
    { "stop_lat",            field_mapping<stop, float,       &stop::latitude>()            },
    { "stop_lon",            field_mapping<stop, float,       &stop::longitude>()           },
    { "zone_id",             field_mapping<stop, std::string, &stop::zone_id>()             },
    { "stop_url",            field_mapping<stop, std::string, &stop::stop_url>()            },
    { "location_type",       field_mapping<stop, int,         &stop::type>()                },
    { "parent_station",      field_mapping<stop, std::string, &stop::parent_id>()           },
    { "stop_timezone",       field_mapping<stop, std::string, &stop::timezone>()            },
    { "wheelchair_boarding", field_mapping<stop, int,         &stop::wheelchair_boarding>() }
  }};
}
