#include <iostream>
#include <sstream>
#include <vector>

#include "datetime.h"
#include "gtfs.h"
#include "timetable.h"
#include "transport.h"


Timetable::Timetable tt("data/citybus");

MsgPack make_payload(std::vector<gtfs::stop_time> visits, std::string date) {
  MsgPack payload;
  payload.pack_array(visits.size());
  for(auto v : visits) {
    std::string arrival = date + " " + v.arrival_time;
    std::string departure = date + " " + v.departure_time;
    std::string route = tt.route_map[tt.trip_map[v.trip_id].route_id].short_name;
    std::string headsign = "a headsign o.o";
    payload.pack(MsgPackArr{arrival, departure, route, headsign});
  }

  return payload;
}

MsgPack do_visits_between(std::string stop_code, DateTime start, DateTime end, int count) {
  auto stop  = tt.stop_map[stop_code];
  // auto route = tt.routes_by_short_name[route_short_name];
  auto start_time = start.time;
  auto end_time   = end.time;

  std::vector<gtfs::stop_time> results;
  for(auto pair : tt.visits_between({stop.id, start_time, "", ""}, {stop.id, end_time, "", ""})) {
    auto visit = pair.second;
    // auto visit_route = tt.route_map[tt.trip_map[visit.trip_id].route_id];
    if(!tt.is_active(visit, start.date)) continue;
    // if(visit_route.id != route.id) continue;

    results.push_back(visit);
    if(results.size() >= count) break;
  }

  return make_payload(results, start.date);
}

MsgPack visits_between(std::string stop, std::string start, std::string end, int count) {
  std::cout << "Received call to `visits_between`: \n"
            << "\tstop:   " << stop << "\n"
            << "\tstart:  " << start << "\n"
            << "\tend:    " << end << "\n"
            << "\tcount:  " << count << "\n";

  auto response_start  = std::chrono::system_clock::now();
  MsgPack result = do_visits_between(stop, start, end, count);
  auto response_end    = std::chrono::system_clock::now();
  std::chrono::duration<double, std::milli> elapsed_time = response_end - response_start;

  std::cout << "Responded in " << elapsed_time.count() << "ms with:\n"
            << result << "\n\n";

  return result;
}


int main() {
  Transport t("ws://shark-nyc1.transio.us:8080/ws");

  // t.procedure("timetable.visits_between",             visits_between);
  // t.procedure("timetable.visits_between_from_route",  visits_between_from_route);
  // t.start();

  visits_between("BUS389", "20170130 06:44:00", "20170130 10:44:00", 2);
  visits_between("BUS389", "20170130 06:44:00", "20170130 10:44:00", 10);

  return 0;
}
