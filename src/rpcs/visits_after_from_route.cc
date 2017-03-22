#include "timetable.h"


MsgPack do_visits_after_from_route(std::string stop_code, DateTime start, std::string route_name, int count) {
  auto stop       = tt.stops[stop_code];
  auto start_time = start.time();
  auto route      = tt.routes_by_short_name[route_name];

  std::vector<Visit> results;
  for(auto pair : tt.visits_at_station(stop.id)) {
    auto visit = pair.second;
    auto visit_route = tt.routes[tt.trips[visit.trip_id].route_id];
    if(!tt.is_active(visit, start.date())) continue;
    if(visit_route.id != route.id) continue;

    results.push_back({visit, start.date(), start.date(), tt});
    if((int) results.size() >= count) break;
  }

  return make_payload(results);
}


MsgPack visits_after_from_route(std::string stop, std::string start, std::string route_name, int count) {
  std::cout << "Received call to `visits_after_from_route`: \n"
            << "\tstop:   " << stop << "\n"
            << "\tstart:  " << start << "\n"
            << "\troute:  " << route_name << "\n"
            << "\tcount:  " << count << "\n";

  auto response_start  = std::chrono::system_clock::now();
  MsgPack result = do_visits_after_from_route(stop, start, route_name, count);
  auto response_end    = std::chrono::system_clock::now();
  std::chrono::duration<double, std::milli> elapsed_time = response_end - response_start;

  std::cout << "Responded in " << elapsed_time.count() << "ms with:\n"
            << result << "\n\n";

  return result;
}

