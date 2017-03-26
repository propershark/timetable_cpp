#pragma once

#include <ctime>
#include <iostream>
#include <iomanip>
#include <map>
#include <unordered_map>

#include "datetime.h"
#include "gtfs.h"

namespace Timetable {
  class Calendar {
    using calendar_t = std::map<DateTime, std::unordered_map<std::string, bool>>;

    public:
      calendar_t calendar;

      Calendar(gtfs::source& source) {
        for(auto cd : source.calendar_date_parser.all()) {
          calendar[DateTime::from_date(cd.date)][cd.service_id] = (cd.exception_type == 1);
        }
      };

      bool service_is_active(std::string service_id, DateTime date) {
        return calendar[date.without_time()][service_id];
      };
  };
}
