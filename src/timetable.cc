#include <iostream>
#include <sstream>
#include <vector>

#include "datetime.h"
#include "timetable.h"
#include "transport.h"


// MsgPackArr next_visits(std::string route, std::string stop_code, DateTime timestamp, int count) {
//   return 1;
// }
// MsgPackArr next_visit(std::string arg1, std::string arg2, DateTime ts) { return next_visits(arg1, arg2, ts, 1); }

// int last_visits(std::string arg1, std::string arg2, DateTime timestamp, int count) {
//   return 1;
// }
// int last_visit(std::string arg1, std::string arg2, DateTime ts) { return last_visits(arg1, arg2, ts, 1); }



int main() {
  Transport t("ws://shark-nyc1.transio.us:8080/ws");

  Timetable::Timetable tt;

  tt.add_visit({ Timetable::Trip("111"), "001" });
  tt.add_visit({ Timetable::Trip("222"), "001" });
  tt.add_visit({ Timetable::Trip("222"), "002" });
  tt.add_visit({ Timetable::Trip("111"), "003" });
  tt.add_visit({ Timetable::Trip("333"), "001" });
  tt.add_visit({ Timetable::Trip("111"), "002" });
  tt.add_visit({ Timetable::Trip("111"), "001" });
  tt.add_visit({ Timetable::Trip("111"), "101" });
  tt.add_visit({ Timetable::Trip("111"), "100" });
  tt.add_visit({ Timetable::Trip("555"), "099" });
  tt.add_visit({ Timetable::Trip("111"), "001" });
  tt.add_visit({ Timetable::Trip("111"), "001" });
  tt.add_visit({ Timetable::Trip("111"), "001" });

  auto iterator = tt.visits_after({"222"}, "004");
  for(; iterator != tt.visit_list.end(); iterator++) {
    auto visit = iterator->second;
    std::cout << visit.trip.id << "-" << visit.departure << "\n";
  }
  // Timetable::Timetable t("data/");

  // t.procedure("timetable.next_visit",   next_visit);
  // t.procedure("timetable.next_visits",  next_visits);
  // t.procedure("timetable.last_visit",   last_visit);
  // t.procedure("timetable.last_visits",  last_visits);
  t.start();


  return 0;
}
