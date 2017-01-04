#pragma once

#include <map>

#include "timetable/types.h"

namespace Timetable {
  struct TripTimestamp {
    Trip trip;
    std::string departure_time;

    TripTimestamp(Trip t, std::string depart) : trip(t), departure_time(depart) {};
    TripTimestamp(Visit v) : TripTimestamp(v.trip, v.departure) {};

    friend bool operator <(const TripTimestamp& a, const TripTimestamp& b) {
      if(a.trip == b.trip) return a.departure_time < b.departure_time;
      return a.trip.id < b.trip.id;
    };
  };

  class Timetable {
    public:
      std::map<TripTimestamp, Visit> visit_list;
      using visit_iterator = std::map<TripTimestamp, Visit>::iterator;

      void add_visit(Visit v) {
        visit_list[v] = v;
      };

      visit_iterator visits_after(Trip t, std::string departure) {
        TripTimestamp tt = { t, departure };
        return visit_list.lower_bound(tt);
      };
  };
}
