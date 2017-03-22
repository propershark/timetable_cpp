#pragma once

#include <map>

#include "datetime.h"
#include "gtfs.h"

namespace Timetable {
  struct visit_list_key {
    std::string station;
    DateTime    time = DateTime::EPOCH;
    std::string route;
    std::string trip;

    enum {
      VLK_STATION,
      VLK_TIME,
      VLK_ROUTE,
      VLK_TRIP
    } fidelity;


    visit_list_key(std::string s, DateTime depart, std::string r, std::string t) : station(s), time(depart), route(r), trip(t), fidelity(VLK_TRIP) {};
    visit_list_key(std::string s, DateTime depart, std::string r) : station(s), time(depart), route(r), fidelity(VLK_ROUTE) {};
    visit_list_key(std::string s, DateTime depart) : station(s), time(depart), fidelity(VLK_TIME) {};
    visit_list_key(std::string s) : station(s), fidelity(VLK_STATION) {};


    visit_list_key  station_only()  const { return {station};                     };
    visit_list_key  time_only()     const { return {station, time};               };
    visit_list_key  route_only()    const { return {station, time, route};        };
    visit_list_key  trip_only()     const { return {station, time, route, trip};  };


    friend bool operator <(const visit_list_key& a, const visit_list_key& b) {
      auto lowest_fidelity = std::min(a.fidelity, b.fidelity);
      switch(lowest_fidelity) {
        case VLK_STATION:
          return a.station < b.station;
        case VLK_TIME:
          return std::tie(a.station, a.time) < std::tie(b.station, b.time);
        case VLK_ROUTE:
          return std::tie(a.station, a.time, a.route) < std::tie(b.station, b.time, b.route);
        case VLK_TRIP:
          return std::tie(a.station, a.time, a.route, a.trip) < std::tie(b.station, b.time, b.route, b.trip);
      }
      return false;
    };

    friend std::ostream& operator<<(std::ostream& os, const visit_list_key& vlk) {
      return os << "["
                << vlk.station  << ", "
                << vlk.time     << ", "
                << vlk.route    << ", "
                << vlk.trip
                << "]";
    };
  };

  using visit_list = std::map<visit_list_key, gtfs::stop_time>;
}
