#pragma once

#include <ostream>
#include <sstream>

#include "mpackCPP/MsgPack.h"
#include "mpackCPP/MsgUnpack.h"

class DateTime {
  public:
    std::string date;
    std::string time;
    std::string string_rep;

    DateTime() : date(""), time(""), string_rep("") {};
    DateTime(std::string date, std::string time) : date(date), time(time), string_rep(date + " " + time) {};
    DateTime(const std::string str) {
      string_rep = str;
      std::stringstream ss(str);
      ss >> date >> time;
    };
    DateTime(MPNode node) : DateTime(std::string(node)) {};

    friend std::ostream& operator<<(std::ostream& os, const DateTime& dt) {
      return os << dt.date << " " << dt.time;
    };

    std::string to_string() { return string_rep; };
};
