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

  tt.add_visit({ { "Trip1" }, "Stop001" });
  tt.add_visit({ { "Trip2" }, "Stop001" });
  tt.add_visit({ { "Trip2" }, "Stop002" });
  tt.add_visit({ { "Trip1" }, "Stop003" });
  tt.add_visit({ { "Trip3" }, "Stop001" });
  tt.add_visit({ { "Trip1" }, "Stop002" });
  tt.add_visit({ { "Trip1" }, "Stop001" });
  tt.add_visit({ { "Trip1" }, "Stop101" });
  tt.add_visit({ { "Trip1" }, "Stop100" });
  tt.add_visit({ { "Trip5" }, "Stop099" });
  tt.add_visit({ { "Trip1" }, "Stop005" });
  tt.add_visit({ { "Trip1" }, "Stop007" });
  tt.add_visit({ { "Trip1" }, "Stop006" });

  auto iterator = tt.visits_before({{"Trip2"}, "Stop004"});
  auto start = iterator.first;
  auto end   = iterator.second;
  for(; start != end; start++) {
    auto visit = start->second;
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
