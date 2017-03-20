#include "timetable/calendar.h"

namespace Timetable {
  std::string _format_date(struct tm& t) {
    char new_date[TIMETABLE_CALENDAR_DATE_LENGTH+1] = { 0 };
    strftime(new_date, TIMETABLE_CALENDAR_DATE_LENGTH, TIMETABLE_CALENDAR_DATE_FORMAT, &t);
    return { new_date };
  }

  void _parse_date(std::string date, struct tm& t) {
    strptime(date.c_str(), TIMETABLE_CALENDAR_DATE_FORMAT, &t);
  }


  std::string next_date(std::string date) {
    struct tm t;
    _parse_date(date, t);
    t.tm_mday += 1;
    return _format_date(t);
  };

  std::string previous_date(std::string date) {
    struct tm t;
    _parse_date(date, t);
    t.tm_mday -= 1;
    return _format_date(t);
  };
}
