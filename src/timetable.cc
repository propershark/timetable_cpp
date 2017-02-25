#include <iostream>
#include <sstream>
#include <vector>

#include "datetime.h"
#include "gtfs.h"
#include "timetable.h"
#include "transport.h"


Timetable::Timetable tt("data/citybus");

MsgPack visits_after(std::string route_short_name, std::string stop_code, DateTime timestamp, int count) {
  auto stop  = tt.stop_map[stop_code];
  auto route = tt.routes_by_short_name[route_short_name];
  auto start_time = timestamp.time;

  std::vector<gtfs::stop_time> results;
  for(auto pair : tt.visits_after({stop.id, route.id, "", start_time})) {
    auto visit = pair.second;
    if(!tt.is_active(visit, timestamp.date)) continue;

    auto route_name     = tt.route_map[tt.trip_map[visit.trip_id].route_id].long_name;
    auto arrival_time   = visit.arrival_time;
    auto departure_time = visit.departure_time;
    auto trip_id        = visit.trip_id;
    std::cout << route_name << "  departs at  " << departure_time << "  on trip  " << trip_id << "\n";
    results.push_back(visit);
    if(results.size() >= count) break;
  }

  MsgPack payload;
  payload.pack_array(results.size());
  for(auto v : results) {
    payload.pack(v.arrival_time);
  }

  return payload;
}

int visits_before(std::string arg1, std::string arg2, DateTime timestamp, int count) {
  return 1;
}



int main() {
  Transport t("ws://shark-nyc1.transio.us:8080/ws");


  t.procedure("timetable.visits_after",   visits_after);
  t.procedure("timetable.visits_before",  visits_before);
  t.start();


  return 0;
}
