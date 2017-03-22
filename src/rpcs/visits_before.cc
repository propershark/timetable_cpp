#include "timetable.h"


MsgPack do_visits_before(std::string stop_code, DateTime end, int count) {
  auto stop     = tt.stops[stop_code];
  auto end_time = end.time();

  std::vector<Visit> results;
  for(auto pair : tt.visits_at_station(stop.id)) {
    auto visit = pair.second;
    if(!tt.is_active(visit, end.date())) continue;

    results.push_back({visit, end.date(), end.date(), tt});
    if((int) results.size() >= count) break;
  }

  return make_payload(results);
}


MsgPack visits_before(std::string stop, std::string end, int count) {
  std::cout << "Received call to `visits_before`: \n"
            << "\tstop:   " << stop << "\n"
            << "\tend:    " << end << "\n"
            << "\tcount:  " << count << "\n";

  auto response_start  = std::chrono::system_clock::now();
  MsgPack result = do_visits_before(stop, end, count);
  auto response_end    = std::chrono::system_clock::now();
  std::chrono::duration<double, std::milli> elapsed_time = response_end - response_start;

  std::cout << "Responded in " << elapsed_time.count() << "ms with:\n"
            << result << "\n\n";

  return result;
}
