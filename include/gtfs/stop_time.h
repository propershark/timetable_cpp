#pragma once

#include <ostream>

#include "gtfs/decls.h"


namespace GTFS {
  class StopTime : public ObjectBase<StopTime, std::string, std::string, std::string, std::string, int, int, int, float> {
    public:
      static std::string table_name;
      // Unique identifier for the trip containing this stop time
      std::string trip_id;
      // Time at which the vehicle should arrive at this stop
      std::string arrival_time;
      // Time at which the vehicle will depart this stop
      std::string departure_time;
      // Identifier of the stop that is the subject of this stop time
      std::string stop_id;
      // Index of this stop time in the containing trip
      int index;
      // Type of pickup offered by the vehicle at this stop time
      int pickup_type;
      // Type of dropoff offered by the vehicle at this stop time
      int dropoff_type;
      // Distance traveled since the previous stop time of the containing trip
      float distance;

      StopTime() = default;
      StopTime(std::string tid, std::string arv_t, std::string dpt_t, std::string sid, int idx, int put, int dot, float dist) : trip_id(tid), arrival_time(arv_t), departure_time(dpt_t), stop_id(sid), index(idx), pickup_type(put), dropoff_type(dot), distance(dist) {};


      // Standard stream output
      friend std::ostream& operator<<(std::ostream& os, const StopTime& s) {
        return os << "StopTime: \n"
          << "\tTrip ID: " << s.trip_id << "\n"
          << "\tArrives at: " << s.arrival_time << "\n"
          << "\tDeparts at: " << s.departure_time << "\n"
          << "\tStop ID: " << s.stop_id << "\n"
          << "\tIndex: " << s.index << "\n"
          << "\tPickup/Dropoff Type: " << s.pickup_type << "/" << s.dropoff_type << "\n"
          << "\tDistance: " << s.distance << "\n";
      };
  };

  std::string StopTime::table_name = "stop_times";
}
