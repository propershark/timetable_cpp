#pragma once

#include <ostream>


namespace gtfs {
  class stop_time {
    public:
      // Identifier for the trip containing this stop time
      std::string trip_id;
      // Time at which the vehicle should arrive at this stop
      std::string arrival_time;
      // Time at which the vehicle will depart this stop
      std::string departure_time;
      // Identifier of the stop that is the subject of this stop time
      std::string stop_id;
      // Index of this stop time in the containing trip
      int index;
      // Text displayed on the bus headsign at this stop time
      std::string headsign;
      // Type of pickup offered by the vehicle at this stop time
      int pickup_type;
      // Type of dropoff offered by the vehicle at this stop time
      int dropoff_type;
      // Distance traveled since the previous stop time of the containing trip
      double distance;
      // Indiciation of whether this stop time is a timepoint
      bool timepoint;

      stop_time() = default;

      void post_init() { };

      // Standard stream output
      friend std::ostream& operator<<(std::ostream& os, const stop_time& st) {
        return os << "stop_time: \n"
          << "\tTrip ID: " << st.trip_id << "\n"
          << "\tArrives at: " << st.arrival_time << "\n"
          << "\tDeparts at: " << st.departure_time << "\n"
          << "\tStop ID: " << st.stop_id << "\n"
          << "\tIndex: " << st.index << "\n"
          << "\tHeadsign Text: " << st.headsign << "\n"
          << "\tPickup/Dropoff Type: " << st.pickup_type << "/" << st.dropoff_type << "\n"
          << "\tDistance: " << st.distance << "\n"
          << "\tTimepoint: " << st.timepoint << "\n";
      };
  };
}
