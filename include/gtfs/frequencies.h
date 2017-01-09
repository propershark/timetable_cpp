#pragma once

#include <ostream>

#include "gtfs/csv_parser.h"


namespace gtfs {
  class frequency {
    static csv_parser<frequency> parser;
    static type_map_t type_map;

    public:
      static std::string file_name;
      // Trip this frequency applies to
      std::string trip_id;
      // Time at which service at this frequency begins
      std::string start_time;
      // Time at which service at this frequency ends
      std::string end_time;
      // Seconds between departures from the same stop (aka "headway")
      int headway;
      // Indication of whether scheduling is done exactly for this trip
      bool exact_times;

      frequency() = default;


      // Standard stream output
      friend std::ostream& operator<<(std::ostream& os, const frequency& f) {
        return os << "frequency: \n"
          << "\tTrip: " << f.trip_id << "\n"
          << "\tStart Time: " << f.start_time << "\n"
          << "\tEnd Time: " << f.end_time << "\n"
          << "\tHeadway Time: " << f.headway_secs << "\n"
          << "\tExact Timing: " << f.exact_times << "\n";
      };
  };

  std::string frequency::file_name = "frequencies.txt";
  type_map_t frequency::type_map = {
    {"trip_id",       type::t_string},
    {"start_time",    type::t_string},
    {"end_time",      type::t_string},
    {"headway_secs",  type::t_int},
    {"exact_times",   type::t_bool}
  };
}
