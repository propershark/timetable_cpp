#include "datetime.h"

// `resolve()` is an attempt at validating the attributes of a DateTime,
// ensuring that all values are within their expected ranges and resolving any
// discrepencies by translating outlying values to the appropriate fields.
//
// For the most part, this is delegated to `mktime`, as dealing with datetime
// ranges quic quickly becomes complex with varying-length months, leap years,
// Daylight Savings Time, etc.
//
// Resolution computes the number of seconds since DateTime::EPOCH. This value
// is returned but can be easily ignored if unneeded.
std::time_t DateTime::resolve() {
  std::tm t;
  // `tm_year` stores years since 1900. `years` is an absolute value.
  t.tm_year  = years - 1900;
  // `tm_mon` starts at 0. `months` is a value in the range [1;12].
  t.tm_mon   = months - 1;
  t.tm_mday  = days;
  t.tm_hour  = hours;
  t.tm_min   = minutes;
  t.tm_sec   = seconds;
  // Defaulting `isdst` to -1 forces `mktime` to determine whether DST is
  // in effect for this datetime.
  t.tm_isdst = -1;

  auto epoch_sec = std::mktime(&t);
  if (epoch_sec == -1)
    throw std::runtime_error("DateTime not representable by mktime");

  this->years   = t.tm_year + 1900;
  this->months  = t.tm_mon + 1;
  this->days    = t.tm_mday;
  this->hours   = t.tm_hour;
  this->minutes = t.tm_min;
  this->seconds = t.tm_sec;

  return epoch_sec;
};
