#pragma once

#include <map>

#include "gtfs.h"

namespace Timetable {
  inline std::string next(std::string arg) { std::string tmp = arg; tmp.back()++; return tmp; };
  inline std::string prev(std::string arg) { std::string tmp = arg; tmp.back()--; return tmp; };

  struct visit_list_key {
    std::string station;
    std::string route;
    std::string trip;
    std::string time;

    visit_list_key(std::string s, std::string depart="", std::string r="", std::string t="") : station(s), time(depart), route(r), trip(t) {};


    visit_list_key  station_lower_bound() const { return {station,        "", "",           ""          }; };
    visit_list_key  station_upper_bound() const { return {next(station),  "", "",           ""          }; };
    visit_list_key    route_lower_bound() const { return {station,        "", route,        ""          }; };
    visit_list_key    route_upper_bound() const { return {station,        "", next(route),  ""          }; };
    visit_list_key     trip_lower_bound() const { return {station,        "", route,        trip        }; };
    visit_list_key     trip_upper_bound() const { return {station,        "", route,        next(trip)  }; };

    friend bool operator <(const visit_list_key& a, const visit_list_key& b) {
      auto a_tie = std::tie(a.station, a.time, a.route, a.trip);
      auto b_tie = std::tie(b.station, b.time, b.route, b.trip);
      return a_tie < b_tie;
    };
  };

  using visit_list = std::map<visit_list_key, gtfs::stop_time>;
}
