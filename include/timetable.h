#pragma once

#include <unordered_map>

#include "minicsv.h"

#include "timetable/route.h"
#include "timetable/stop.h"
#include "timetable/visit.h"


namespace Timetable {
  std::unordered_map<Route, Trip> schedule;
  std::unordered_map<std::string, Trip> trip_list;
  std::unordered_map<std::string, Stop> stop_list;

  void initialize(std::string gtfs_archive) {
    mini::csv::ifstream stops_is("data/stops.txt");
    stops_is.set_delimiter(',', "$$");
    stops_is.read_line();
    while(stops_is.read_line()) {
      Stop s;
      stops_is >> s.id >> s.code >> s.name;
      stop_list[s.id] = s;
    }

    stops_is.close();

    mini::csv::ifstream stis("data/stop_times.txt");
    stis.set_delimiter(',', "$$");
    stis.read_line();
    while(stis.read_line()) {
      std::string trip_id;
      stis >> trip_id;

      Visit v;
      std::string stop_id;
      stis >> v.arrival >> v.departure >> stop_id >> v.index >> v.pickup_type >> v.dropoff_type >> v.distance_traveled;
      v.stop = stop_list[stop_id];

      trip_list[trip_id].push_back(v);
    }

    stis.close();

    for(auto&& trip : trip_list) {
      std::cout << trip.first << ":" << trip.second.size() << "\n";
    }
  };
}
