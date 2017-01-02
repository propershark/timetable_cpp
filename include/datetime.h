#include "mpackCPP/MsgUnpack.h"
#include <ostream>
#include <sstream>

class DateTime {
  public:
    std::string date;
    std::string time;

    DateTime() : date(""), time("") {};
    DateTime(const std::string str) {
      std::stringstream ss(str);
      ss >> date >> time;
    };
    DateTime(MPNode node) : DateTime(std::string(node)) {};

    friend std::ostream& operator<<(std::ostream& os, const DateTime& dt) {
      return os << dt.date << " " << dt.time;
    }
};
