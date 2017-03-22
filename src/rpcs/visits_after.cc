#include "timetable.h"


MsgPack do_visits_after(std::string stop_code, DateTime start, int count) {
  auto stop       = tt.stops[stop_code];
  auto start_time = start.time();

  std::vector<Visit> results;
  for(auto pair : tt.visits_at_station(stop.id)) {
    auto visit = pair.second;
    if(!tt.is_active(visit, start.date())) continue;

    results.push_back({visit, start.date(), start.date(), tt});
    if((int) results.size() >= count) break;
  }

  return make_payload(results);
}


MsgPack visits_after(std::string stop, std::string start, int count) {
  std::cout << "Received call to `visits_after`: \n"
            << "\tstop:   " << stop << "\n"
            << "\tstart:  " << start << "\n"
            << "\tcount:  " << count << "\n";

  auto response_start  = std::chrono::system_clock::now();
  MsgPack result = do_visits_after(stop, start, count);
  auto response_end    = std::chrono::system_clock::now();
  std::chrono::duration<double, std::milli> elapsed_time = response_end - response_start;

  std::cout << "Responded in " << elapsed_time.count() << "ms with:\n"
            << result << "\n\n";

  return result;
}

