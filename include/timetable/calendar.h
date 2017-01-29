#pragma once

#include <unordered_map>

#include "gtfs.h"


namespace Timetable {
  class Calendar {
    using calendar_t = std::unordered_map<std::string, std::unordered_map<std::string, bool>>;

    public:
      std::string archive_dir;
      calendar_t calendar;

      Calendar(std::string directory) : archive_dir(directory) {
        for(auto cd : gtfs::calendar_date::parser.all(archive_dir)) {
          calendar[cd.service_id][cd.date] = (cd.exception_type == 1);
        }
      };

      bool service_is_active(std::string service_id, std::string date) {
        return calendar[service_id][date];
      };
  };
}
