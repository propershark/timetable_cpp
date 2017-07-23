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
    using calendar_dates_t = std::map<DateTime, std::unordered_map<std::string, bool>>;
    using calendar_t       = std::unordered_map<std::string, gtfs::calendar>;
    using service_date_t   = std::unordered_map<std::string, DateTime>;

    public:
      calendar_dates_t exceptions;
      calendar_t calendar;
      service_date_t start_date;
      service_date_t end_date;

      Calendar(gtfs::source& source) {
        for(auto record : source.calendar_parser.all()) {
          calendar[record.service_id] = record;
          start_date[record.service_id] = DateTime::from_date(record.start_date);
          end_date[record.service_id] = DateTime::from_date(record.end_date);
        }

        for(auto cd : source.calendar_date_parser.all()) {
          exceptions[DateTime::from_date(cd.date)][cd.service_id] = (cd.exception_type == 1);
        }
      };

      bool service_is_active(std::string service_id, DateTime date) {
        for (auto it = exceptions.find(date); it != exceptions.end(); ++it)
          for (auto exception_active = it->second.find(service_id); exception_active != it->second.end();)
            return exception_active->second;

        if (date < start_date[service_id] || date > end_date[service_id])
          return false;

        switch (date.weekday()) {
          case DateTime::MONDAY:    return calendar[service_id].monday;
          case DateTime::TUESDAY:   return calendar[service_id].tuesday;
          case DateTime::WEDNESDAY: return calendar[service_id].wednesday;
          case DateTime::THURSDAY:  return calendar[service_id].thursday;
          case DateTime::FRIDAY:    return calendar[service_id].friday;
          case DateTime::SATURDAY:  return calendar[service_id].saturday;
          case DateTime::SUNDAY:    return calendar[service_id].sunday;
        }
      };
  };
}
