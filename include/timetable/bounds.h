#pragma once

#include "timetable/visit_list.h"

namespace Timetable {
  template<typename It>
  class bounds_template {
    It first;
    It second;

    public:
      bounds_template(It start, It end) : first(start), second(end) {};
      bounds_template(const bounds_template& other) : first(other.first), second(other.second) {};

      It begin()  { return first;   };
      It end()    { return second;  };
  };

  using bounds_t          = bounds_template<visit_list::const_iterator>;
  using reverse_bounds_t  = bounds_template<visit_list::const_reverse_iterator>;

  template<typename BoundsType>
  reverse_bounds_t reverse(BoundsType bounds) {
    return { std::make_reverse_iterator(bounds.end()), std::make_reverse_iterator(bounds.begin()) };
  };
}
