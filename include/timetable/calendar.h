#pragma once

#include <unordered_map>

#include "gtfs.h"


namespace Timetable {
  class Calendar {
    using calendar_t = std::unordered_map<std::string, std::unordered_map<std::string, bool>>;

    public:
      calendar_t calendar;

      Calendar(gtfs::source& source) {
        for(auto cd : source.calendar_dates.all()) {
          calendar[cd.service_id][cd.date] = (cd.exception_type == 1);
        }
      };

      bool service_is_active(std::string service_id, std::string date) {
        return calendar[service_id][date];
      };
  };
}
