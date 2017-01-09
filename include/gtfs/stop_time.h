#pragma once

#include <ostream>

#include "gtfs/csv_parser.h"


namespace gtfs {
  class stop_time {
    static csv_parser<stop_time> parser;
    static type_map_t type_map;

    public:
      static std::string file_name;
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
      std::string stop_headsign;
      // Type of pickup offered by the vehicle at this stop time
      int pickup_type;
      // Type of dropoff offered by the vehicle at this stop time
      int dropoff_type;
      // Distance traveled since the previous stop time of the containing trip
      float distance;
      // Indiciation of whether this stop time is a timepoint
      bool timepoint;

      stop_time() = default;


      // Standard stream output
      friend std::ostream& operator<<(std::ostream& os, const stop_time& st) {
        return os << "stop_time: \n"
          << "\tTrip ID: " << st.trip_id << "\n"
          << "\tArrives at: " << st.arrival_time << "\n"
          << "\tDeparts at: " << st.departure_time << "\n"
          << "\tStop ID: " << st.stop_id << "\n"
          << "\tIndex: " << st.index << "\n"
          << "\tHeadsign Text: " << st.stop_headsign << "\n"
          << "\tPickup/Dropoff Type: " << st.pickup_type << "/" << st.dropoff_type << "\n"
          << "\tDistance: " << st.distance << "\n"
          << "\tTimepoint: " << st.timepoint << "\n";
      };
  };

  std::string stop_time::file_name = "stop_times.txt";
  type_map_t stop_time::type_map = {
    {"trip_id",             type::t_string},
    {"arrival_time",        type::t_string},
    {"departure_time",      type::t_string},
    {"stop_id",             type::t_string},
    {"stop_sequence",       type::t_int},
    {"stop_headsign",       type::t_string},
    {"pickup_type",         type::t_int},
    {"dropoff_type",        type::t_int},
    {"shape_dist_traveled", type::t_float},
    {"timepoint",           type::t_bool}
  };
}
