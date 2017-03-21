#include "datetime.h"

bool DateTime::operator<(DateTime& b) const {
  auto a_tie = std::tie(  years,   months,   days,   hours,   minutes,   seconds);
  auto b_tie = std::tie(b.years, b.months, b.days, b.hours, b.minutes, b.seconds);
  return a_tie < b_tie;
};

bool DateTime::operator>(DateTime& b) const {
  auto a_tie = std::tie(  years,   months,   days,   hours,   minutes,   seconds);
  auto b_tie = std::tie(b.years, b.months, b.days, b.hours, b.minutes, b.seconds);
  return a_tie > b_tie;
};

bool DateTime::operator==(DateTime& b) const {
  auto a_tie = std::tie(  years,   months,   days,   hours,   minutes,   seconds);
  auto b_tie = std::tie(b.years, b.months, b.days, b.hours, b.minutes, b.seconds);
  return a_tie == b_tie;
};


template<> DateTime& DateTime::operator++<DateTime::YEAR>()   { years++;    resolve(); return *this; };
template<> DateTime& DateTime::operator++<DateTime::MONTH>()  { months++;   resolve(); return *this; };
template<> DateTime& DateTime::operator++<DateTime::DAY>()    { days++;     resolve(); return *this; };
template<> DateTime& DateTime::operator++<DateTime::HOUR>()   { hours++;    resolve(); return *this; };
template<> DateTime& DateTime::operator++<DateTime::MINUTE>() { minutes++;  resolve(); return *this; };
template<> DateTime& DateTime::operator++<DateTime::SECOND>() { seconds++;  resolve(); return *this; };

template<> DateTime& DateTime::operator--<DateTime::YEAR>()   { years--;    resolve(); return *this; };
template<> DateTime& DateTime::operator--<DateTime::MONTH>()  { months--;   resolve(); return *this; };
template<> DateTime& DateTime::operator--<DateTime::DAY>()    { days--;     resolve(); return *this; };
template<> DateTime& DateTime::operator--<DateTime::HOUR>()   { hours--;    resolve(); return *this; };
template<> DateTime& DateTime::operator--<DateTime::MINUTE>() { minutes--;  resolve(); return *this; };
template<> DateTime& DateTime::operator--<DateTime::SECOND>() { seconds--;  resolve(); return *this; };

template<> DateTime DateTime::operator++<DateTime::YEAR>(int)   { years++;    resolve(); return *this; };
template<> DateTime DateTime::operator++<DateTime::MONTH>(int)  { months++;   resolve(); return *this; };
template<> DateTime DateTime::operator++<DateTime::DAY>(int)    { days++;     resolve(); return *this; };
template<> DateTime DateTime::operator++<DateTime::HOUR>(int)   { hours++;    resolve(); return *this; };
template<> DateTime DateTime::operator++<DateTime::MINUTE>(int) { minutes++;  resolve(); return *this; };
template<> DateTime DateTime::operator++<DateTime::SECOND>(int) { seconds++;  resolve(); return *this; };

template<> DateTime DateTime::operator--<DateTime::YEAR>(int)   { years--;    resolve(); return *this; };
template<> DateTime DateTime::operator--<DateTime::MONTH>(int)  { months--;   resolve(); return *this; };
template<> DateTime DateTime::operator--<DateTime::DAY>(int)    { days--;     resolve(); return *this; };
template<> DateTime DateTime::operator--<DateTime::HOUR>(int)   { hours--;    resolve(); return *this; };
template<> DateTime DateTime::operator--<DateTime::MINUTE>(int) { minutes--;  resolve(); return *this; };
template<> DateTime DateTime::operator--<DateTime::SECOND>(int) { seconds--;  resolve(); return *this; };


DateTime& DateTime::operator+=(DateTime& other) {
  this->years   += other.years;
  this->months  += other.months;
  this->days    += other.days;
  this->hours   += other.hours;
  this->minutes += other.minutes;
  this->seconds += other.seconds;
  return *this;
};

DateTime& DateTime::operator-=(DateTime& other) {
  this->years   -= other.years;
  this->months  -= other.months;
  this->days    -= other.days;
  this->hours   -= other.hours;
  this->minutes -= other.minutes;
  this->seconds -= other.seconds;
  return *this;
};


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