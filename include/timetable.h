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

    visit_list_key route_lower_bound() const { return {route,        {""}, {}}; };
    visit_list_key route_upper_bound() const { return {route.inc(),  {""}, {}}; };
    visit_list_key  trip_lower_bound() const { return {route,        trip, {}}; };
    visit_list_key  trip_upper_bound() const { return {route,  trip.inc(), {}}; };

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
      using bounds_t          = std::pair<iterator, iterator>;
      using reverse_bounds_t  = std::pair<reverse_iterator, reverse_iterator>;

      reverse_bounds_t reverse(bounds_t bounds) const {
        return { std::make_reverse_iterator(bounds.second), std::make_reverse_iterator(bounds.first) };
      };

      bounds_t reverse(reverse_bounds_t bounds) const {
        return { bounds.second.base(), bounds.first.base() };
      };

      list_t visit_list;

      void add_visit(Visit v) {
        visit_list[v] = v;
      };

      bounds_t visits_after(const visit_list_key key) const {
        auto lower_bound = visit_list.lower_bound(key);
        auto upper_bound = visit_list.upper_bound(key.route_upper_bound());
        return { lower_bound, upper_bound };
      };

      reverse_bounds_t visits_before(const visit_list_key key) const {
        auto lower_bound = visit_list.lower_bound(key.trip_lower_bound());
        auto upper_bound = visit_list.upper_bound(key);
        bounds_t bounds{ lower_bound, upper_bound };
        return reverse(bounds);
      };
  };
}
