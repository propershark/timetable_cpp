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

  tt.add_visit({"Route 1", "Trip 1", "Stop001", "000"});
  tt.add_visit({"Route 1", "Trip 1", "Stop003", "111"});
  tt.add_visit({"Route 1", "Trip 1", "Stop004", "222"});
  tt.add_visit({"Route 1", "Trip 1", "Stop004", "333"});
  tt.add_visit({"Route 2", "Trip 1", "Stop001", "333"});
  tt.add_visit({"Route 2", "Trip 1", "Stop003", "444"});
  tt.add_visit({"Route 2", "Trip 1", "Stop001", "555"});
  tt.add_visit({"Route 2", "Trip 1", "Stop002", "666"});
  tt.add_visit({"Route 1", "Trip 2", "Stop002", "777"});
  tt.add_visit({"Route 1", "Trip 1", "Stop002", "888"});

  auto iterator = tt.visits_after({"Route 1", "Trip 1", "888"});
  for(auto&& pair : iterator) {
    auto visit = pair.second;
    std::cout << visit.route_id << "-" << visit.trip_id << "-" << visit.departure << "\n";
  }
  // Timetable::Timetable t("data/");

  // t.procedure("timetable.next_visit",   next_visit);
  // t.procedure("timetable.next_visits",  next_visits);
  // t.procedure("timetable.last_visit",   last_visit);
  // t.procedure("timetable.last_visits",  last_visits);
  t.start();


  return 0;
}
