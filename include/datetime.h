#pragma once

#include <iostream>
#include <ostream>
#include <sstream>


class DateTime {
  public:
    enum Unit {
      YEAR,
      MONTH,
      DAY,
      HOUR,
      MINUTE,
      SECOND
    };


    short years;
    short months;
    short days;

    short hours;
    short minutes;
    short seconds;


    DateTime() : years(0), months(0), days(0), hours(0), minutes(0), seconds(0) {};
    DateTime(short y, short m, short d, short h, short i, short s) : years(y), months(m), days(d), hours(h), minutes(i), seconds(s) {};
    DateTime(std::string dt) {
      sscanf(dt.c_str(), "%4hd%2hd%2hd %2hd:%2hd:%2hd", &years, &months, &days, &hours, &minutes, &seconds);
    };
    DateTime(std::string date, std::string time) {
      sscanf(date.c_str(), "%4hd%2hd%2hd", &years, &months, &days);
      sscanf(time.c_str(), "%2hd:%2hd:%2hd", &hours, &minutes, &seconds);
    };

    bool operator< (DateTime& other) const;
    bool operator> (DateTime& other) const;
    bool operator<=(DateTime& other) const { return !this->operator>(other); };
    bool operator>=(DateTime& other) const { return !this->operator<(other); };

    bool operator==(DateTime& other) const;
    bool operator!=(DateTime& other) const { return !this->operator==(other); };

    // Increment/Decrement this DateTime by 1 of the given unit. With no
    // template argument, the unit will default to 1 day.
    template<Unit unit=DAY>
    DateTime& operator++();
    template<Unit unit=DAY>
    DateTime& operator--();
    template<Unit unit=DAY>
    DateTime  operator++(int);
    template<Unit unit=DAY>
    DateTime  operator--(int);

    // Arithmetic operations for DateTimes. Multiplication and Division are
    // non-sensical operations for DateTimes, and are thus not defined.
    DateTime& operator+=(DateTime& other);
    DateTime& operator-=(DateTime& other);
    DateTime  operator+ (DateTime& other) const { DateTime dt(*this); dt += other; return dt; };
    DateTime  operator- (DateTime& other) const { DateTime dt(*this); dt -= other; return dt; };

    // Ensure that all values are within their bounds, carrying over surplus
    // values to higher unit places (e.g., 32 days becomes 1 month + 1-4 days).
    void resolve();

    // Return the string representation of this DateTime as `YYYYMMDD`.
    std::string date() const;
    // Return the string representation of this DateTime as `hh:mm:ss`.
    std::string time() const;
    // Return the string representation of this DateTime following the default
    // format `YYYYMMDD hh:mm:ss`.
    std::string to_string() const;

    // Output the string returned by `to_string()` to the given stream.
    friend std::ostream& operator<<(std::ostream& os, const DateTime& dt) {
      return os << dt.to_string();
    };
};
