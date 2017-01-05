#pragma once

#include <map>

#include "timetable/types.h"

namespace Timetable {
  struct visit_list_key {
    Route route;
    Trip trip;
    std::string departure_time;

    visit_list_key(Route r, Trip t, std::string depart) : route(r), trip(t), departure_time(depart) {};
    visit_list_key(Trip t, std::string depart) : route(t.route), trip(t), departure_time(depart) {};
    visit_list_key(Visit v) : visit_list_key(v.trip, v.departure) {};

    friend bool operator <(const visit_list_key& a, const visit_list_key& b) {
      return  a.route != b.route ? a.route.id < b.route.id :
              a.trip  != b.trip  ? a.trip.id  < b.trip.id  :
              a.departure_time < b.departure_time;
    };
  };

  class Timetable {
    public:
      using list_t            = std::map<visit_list_key, Visit>;
      using iterator          = list_t::const_iterator;
      using reverse_iterator  = std::reverse_iterator<list_t::const_iterator>;

      list_t visit_list;

      void add_visit(Visit v) {
        visit_list[v] = v;
      };

      iterator visits_after(const visit_list_key key) const {
        return visit_list.lower_bound(key);
      };

      reverse_iterator visits_before(const visit_list_key key) const {
        return std::make_reverse_iterator(visit_list.upper_bound(key));
      };
  };
}
