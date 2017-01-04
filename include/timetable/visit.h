#pragma once

#include <vector>

#include "timetable/stop.h"

namespace Timetable {
  enum class BarkationType {
   SCHEDULED,
   NOT_AVAILABLE,
   AGENCY_CONTACT_REQUIRED,
   DRIVER_CONTACT_REQUIRED
  };

  class Visit {
    public:
      std::string arrival;
      std::string departure;

      Stop stop;

      int pickup_type;
      int dropoff_type;

      int index;
      float distance_traveled;
      bool is_timepoint;
  };

  using Trip = std::vector<Visit>;
}
