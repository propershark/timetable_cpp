#include "timetable.h"


MsgPack do_visits_between(std::string stop_code, DateTime start, DateTime end, int count) {
  auto stop       = tt.stops[stop_code];
  auto start_time = start.time;
  auto end_time   = end.time;

  std::vector<Visit> results;
  for(auto pair : tt.visits_between({stop.id, start_time, "", ""}, {stop.id, end_time, "", ""})) {
    auto visit = pair.second;
    if(!tt.is_active(visit, start.date)) continue;

    results.push_back({visit, start.date, start.date, tt});
    if(results.size() >= count) break;
  }

  return make_payload(results);
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
