#pragma once

#include <ctime>
#include <iostream>
#include <iomanip>
#include <unordered_map>

#include "gtfs.h"

// Following the GTFS date format (%Y%m%d), a date will always be 8 characters
// in length: 4 for the year, 2 for the month, and 2 for the day.
// Should these values change, the format MUST be lexicographically comparable.
#define TIMETABLE_CALENDAR_DATE_FORMAT "%Y%m%d"
#define TIMETABLE_CALENDAR_DATE_LENGTH 8

namespace Timetable {
  class Calendar {
    using calendar_t = std::unordered_map<std::string, std::unordered_map<std::string, bool>>;

    public:
      calendar_t calendar;

      Calendar(gtfs::source& source) {
        for(auto cd : source.calendar_date_parser.all()) {
          calendar[cd.service_id][cd.date] = (cd.exception_type == 1);
        }
      };

      bool service_is_active(std::string service_id, std::string date) {
        return calendar[service_id][date];
      };
  };

  std::string next_date(std::string date);
  std::string previous_date(std::string date);
}
