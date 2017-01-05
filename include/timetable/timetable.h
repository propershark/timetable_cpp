#pragma once

#include <map>

#include "timetable/types.h"


namespace Timetable {
  class Timetable {
    public:
      Timetable() = default;

      visit_list visits;

      void add_visit(Visit v) {
        visits[v] = v;
      };

      bounds_t visits_after(const visit_list_key key) const {
        auto lower_bound = visits.lower_bound(key);
        auto upper_bound = visits.upper_bound(key.route_upper_bound());
        return { lower_bound, upper_bound };
      };

      reverse_bounds_t visits_before(const visit_list_key key) const {
        auto lower_bound = visits.lower_bound(key.trip_lower_bound());
        auto upper_bound = visits.upper_bound(key);
        bounds_t bounds{ lower_bound, upper_bound };
        return reverse(bounds);
      };
  };
}
