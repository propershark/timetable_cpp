#include <iostream>
#include <sstream>
#include <vector>

#include "datetime.h"
#include "gtfs.h"
#include "timetable.h"
#include "transport.h"


Timetable::Timetable tt("data/citybus");

MsgPack make_payload(std::vector<gtfs::stop_time> visits) {
  MsgPack payload;
  payload.pack_array(visits.size());
  for(auto v : visits)
    payload.pack(MsgPackArr{v.arrival_time, v.departure_time});

  return payload;
}

MsgPack visits_after(std::string route_short_name, std::string stop_code, DateTime timestamp, int count) {
  auto stop  = tt.stop_map[stop_code];
  auto route = tt.routes_by_short_name[route_short_name];
  auto start_time = timestamp.time;

  std::vector<gtfs::stop_time> results;
  for(auto pair : tt.visits_after({stop.id, start_time, route.id, ""})) {
    auto visit = pair.second;
    if(!tt.is_active(visit, timestamp.date)) continue;

    results.push_back(visit);
    if(results.size() >= count) break;
  }

  return make_payload(results);
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
