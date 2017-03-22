#include "datetime.h"

// The default constructor for DateTime is set to the UNIX epoch.
DateTime DateTime::EPOCH = DateTime();

DateTime DateTime::from_date(std::string date) {
  DateTime dt(date, "00:00:00");
  dt.resolve();
  return dt;
};

DateTime DateTime::from_time(std::string time) {
  DateTime dt("19700101", time);
  dt.resolve();
  return dt;
};

inline auto as_tuple(const DateTime& dt) { return std::tie(dt.years, dt.months, dt.days, dt.hours, dt.minutes, dt.seconds); };

bool DateTime::operator< (const DateTime& b) const {
  return as_tuple(*this) < as_tuple(b);
};

bool DateTime::operator> (const DateTime& b) const {
  return as_tuple(*this) > as_tuple(b);
};

bool DateTime::operator==(const DateTime& b) const {
  return as_tuple(*this) == as_tuple(b);
};


template<> DateTime& DateTime::operator++<DateTime::YEAR>()   { years++;    resolve(); return *this; };
template<> DateTime& DateTime::operator++<DateTime::MONTH>()  { months++;   resolve(); return *this; };
template<> DateTime& DateTime::operator++<DateTime::WEEK>()   { days += 7;  resolve(); return *this; };
template<> DateTime& DateTime::operator++<DateTime::DAY>()    { days++;     resolve(); return *this; };
template<> DateTime& DateTime::operator++<DateTime::HOUR>()   { hours++;    resolve(); return *this; };
template<> DateTime& DateTime::operator++<DateTime::MINUTE>() { minutes++;  resolve(); return *this; };
template<> DateTime& DateTime::operator++<DateTime::SECOND>() { seconds++;  resolve(); return *this; };

template<> DateTime& DateTime::operator--<DateTime::YEAR>()   { years--;    resolve(); return *this; };
template<> DateTime& DateTime::operator--<DateTime::MONTH>()  { months--;   resolve(); return *this; };
template<> DateTime& DateTime::operator--<DateTime::WEEK>()   { days -= 7;  resolve(); return *this; };
template<> DateTime& DateTime::operator--<DateTime::DAY>()    { days--;     resolve(); return *this; };
template<> DateTime& DateTime::operator--<DateTime::HOUR>()   { hours--;    resolve(); return *this; };
template<> DateTime& DateTime::operator--<DateTime::MINUTE>() { minutes--;  resolve(); return *this; };
template<> DateTime& DateTime::operator--<DateTime::SECOND>() { seconds--;  resolve(); return *this; };

template<> DateTime DateTime::operator++<DateTime::YEAR>(int)   { years++;    resolve(); return *this; };
template<> DateTime DateTime::operator++<DateTime::MONTH>(int)  { months++;   resolve(); return *this; };
template<> DateTime DateTime::operator++<DateTime::WEEK>(int)   { days += 7;  resolve(); return *this; };
template<> DateTime DateTime::operator++<DateTime::DAY>(int)    { days++;     resolve(); return *this; };
template<> DateTime DateTime::operator++<DateTime::HOUR>(int)   { hours++;    resolve(); return *this; };
template<> DateTime DateTime::operator++<DateTime::MINUTE>(int) { minutes++;  resolve(); return *this; };
template<> DateTime DateTime::operator++<DateTime::SECOND>(int) { seconds++;  resolve(); return *this; };

template<> DateTime DateTime::operator--<DateTime::YEAR>(int)   { years--;    resolve(); return *this; };
template<> DateTime DateTime::operator--<DateTime::MONTH>(int)  { months--;   resolve(); return *this; };
template<> DateTime DateTime::operator--<DateTime::WEEK>(int)   { days -= 7;  resolve(); return *this; };
template<> DateTime DateTime::operator--<DateTime::DAY>(int)    { days--;     resolve(); return *this; };
template<> DateTime DateTime::operator--<DateTime::HOUR>(int)   { hours--;    resolve(); return *this; };
template<> DateTime DateTime::operator--<DateTime::MINUTE>(int) { minutes--;  resolve(); return *this; };
template<> DateTime DateTime::operator--<DateTime::SECOND>(int) { seconds--;  resolve(); return *this; };


DateTime& DateTime::operator+=(const DateTime& other) {
  this->years   += other.years;
  this->months  += other.months;
  this->days    += other.days;
  this->hours   += other.hours;
  this->minutes += other.minutes;
  this->seconds += other.seconds;
  return *this;
};

DateTime& DateTime::operator-=(const DateTime& other) {
  this->years   -= other.years;
  this->months  -= other.months;
  this->days    -= other.days;
  this->hours   -= other.hours;
  this->minutes -= other.minutes;
  this->seconds -= other.seconds;
  return *this;
};


DateTime DateTime::without_date() {
  DateTime dt(*this);
  dt.years  = 0;
  dt.months = 0;
  dt.days   = 0;
  dt.resolve();
  return dt;
};

DateTime DateTime::without_time() {
  DateTime dt(*this);
  dt.hours    = 0;
  dt.minutes  = 0;
  dt.seconds  = 0;
  dt.resolve();
  return dt;
}


std::string DateTime::date() const {
  char buf[9] = { 0 };
  snprintf(buf, 9, "%04d%02d%02d", years, months, days);
  return { buf };
};

std::string DateTime::time() const {
  char buf[9] = { 0 };
  snprintf(buf, 9, "%02d:%02d:%02d", hours, minutes, seconds);
  return { buf };
};

std::string DateTime::to_string() const {
  char buf[18] = { 0 };
  snprintf(buf, 18, "%04d%02d%02d %02d:%02d:%02d", years, months, days, hours, minutes, seconds);
  return { buf };
};
