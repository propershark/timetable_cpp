#pragma once

#include <ostream>


namespace gtfs {
  class frequency {
    public:
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

      void post_init() { };

      // Standard stream output
      friend std::ostream& operator<<(std::ostream& os, const frequency& f) {
        return os << "frequency: \n"
          << "\tTrip: " << f.trip_id << "\n"
          << "\tStart Time: " << f.start_time << "\n"
          << "\tEnd Time: " << f.end_time << "\n"
          << "\tHeadway Time: " << f.headway << "\n"
          << "\tExact Timing: " << f.exact_times << "\n";
      };
  };
}
