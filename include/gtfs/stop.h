#pragma once

#include <ostream>


namespace gtfs {
  class stop {
    public:
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

      void post_init() {
        if (code.empty()) code = id;
      };

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
}
