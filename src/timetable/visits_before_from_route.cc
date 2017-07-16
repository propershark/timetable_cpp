#include "timetable.h"


MsgPack do_visits_before_from_route(std::string stop_code, DateTime end, std::string route_name, int count) {
  std::vector<Visit> results;
  auto &index = tt->st_indices["route.station.departure"];
  auto stop   = tt->stops[stop_code];
  auto route  = std::find_if(tt->routes.begin(), tt->routes.end(), [route_name](auto pair) {
    if(pair.second.short_name == route_name) return true;
    return false;
  })->second;

  auto upper_bound    = index.upper_bound(Timetable::next(route.id + stop.id));
  auto initial_bound  = index.upper_bound(route.id + stop.id + end.time());

  for(auto today = end.without_time(); ; today--) {
    auto bound = today.date() == end.date() ? initial_bound : upper_bound--;

    for(auto it = bound; ; --it) {
      auto stop_time = *it->second;
      if(stop_time.stop_id != stop.id) break;
      if(!tt->is_active(stop_time, today)) continue;

      auto departure_dt = DateTime(today.date(), stop_time.departure_time);
      departure_dt.resolve();

      results.push_back({stop_time, departure_dt, departure_dt, *tt});

      if((int) results.size() >= count) goto finish;
    }
  }

  finish:
  return make_payload(results);
}


MsgPack visits_before_from_route(std::string stop, std::string end, std::string route_name, int count) {
  std::cout << "Received call to `visits_before_from_route`: \n"
            << "\tstop:   " << stop << "\n"
            << "\tend:    " << end << "\n"
            << "\troute:  " << route_name << "\n"
            << "\tcount:  " << count << "\n";

  auto response_start  = std::chrono::system_clock::now();
  MsgPack result = do_visits_before_from_route(stop, end, route_name, count);
  auto response_end    = std::chrono::system_clock::now();
  std::chrono::duration<double, std::milli> elapsed_time = response_end - response_start;

  std::cout << "Responded in " << elapsed_time.count() << "ms with:\n"
            << result << "\n\n";

  return result;
}

