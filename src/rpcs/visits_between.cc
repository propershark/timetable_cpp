#include "timetable.h"


MsgPack do_visits_between(std::string stop_code, DateTime start, DateTime end, int count) {
  auto stop       = tt.stops[stop_code];
  auto start_time = start.time;
  auto end_time   = end.time;

  std::vector<Visit> results;

  std::string current_date = start.date;
  while(current_date <= end.date) {
    std::cout << current_date << "\n";

    for(auto pair : tt.visits_between({stop.id, "", "", ""}, {stop.id, "", "", ""})) {
      auto stop_time = pair.second;
      if(stop_time.stop_id != stop.id) goto finish;

      if(current_date == start.date && stop_time.departure_time < start_time) continue;
      if(current_date == end.date   && stop_time.departure_time > end_time)   goto finish;

      if(!tt.is_active(stop_time, current_date)) continue;

      results.push_back({stop_time, current_date, current_date, tt});
      if((int) results.size() >= count) goto finish;
    }

    std::cout << "Iterating date from "  << current_date;
    current_date = Timetable::next_date(current_date);
    std::cout << " to "  << current_date << "\n";
  }

  finish:
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
