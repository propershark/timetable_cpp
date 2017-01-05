#pragma once

#include <map>

#include "timetable/types.h"

namespace Timetable {
  inline std::string next(std::string arg) { std::string tmp = arg; tmp.back()++; return tmp; };
  inline std::string prev(std::string arg) { std::string tmp = arg; tmp.back()--; return tmp; };

  struct visit_list_key {
    std::string route;
    std::string trip;
    std::string time;

    visit_list_key(std::string r, std::string t, std::string depart) : route(r), trip(t), time(depart) {};
    visit_list_key(Visit v) : visit_list_key(v.route_id, v.trip_id, v.departure) {};


    visit_list_key route_lower_bound() const { return {route,         "", ""}; };
    visit_list_key route_upper_bound() const { return {next(route),   "", ""}; };
    visit_list_key  trip_lower_bound() const { return {route,       trip, ""}; };
    visit_list_key  trip_upper_bound() const { return {route, next(trip), ""}; };

    friend bool operator <(const visit_list_key& a, const visit_list_key& b) {
      auto a_tie = std::tie(a.route, a.trip, a.time);
      auto b_tie = std::tie(b.route, b.trip, b.time);
      return a_tie < b_tie;
    };
  };

  using visit_list        = std::map<visit_list_key, Visit>;
  using iterator          = visit_list::const_iterator;
  using reverse_iterator  = std::reverse_iterator<iterator>;
}
