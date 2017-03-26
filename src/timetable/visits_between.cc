#include "timetable.h"


MsgPack do_visits_between(std::string stop_code, DateTime start, DateTime end, int count) {
  auto& index       = tt.st_indices["station.departure"];
  auto stop         = tt.stops[stop_code];
  auto lower_bound  = index.lower_bound(stop.id);

  std::vector<Visit> results;
  DateTime current_date = start.without_time();
  while(current_date <= end) {
    for(auto it = lower_bound; ; ++it) {
      auto stop_time = *it->second;
      if(stop_time.stop_id != stop.id) goto next_date;

      auto departure_dt = DateTime(current_date.date(), stop_time.departure_time);
      departure_dt.resolve();
      if(departure_dt < start)  continue;
      if(departure_dt > end)    goto finish;

      if(!tt.is_active(stop_time, current_date)) continue;

      results.push_back({stop_time, departure_dt, departure_dt, tt});
      if((int) results.size() >= count) goto finish;
    }

    next_date:
    current_date++;
  }

  finish:
  return make_payload(results);
}


MsgPack visits_between(std::string stop, std::string start, std::string end, int count) {
  std::cout << "Received call to `visits_between`: \n"
            << "\tstop:   " << stop   << "\n"
            << "\tstart:  " << start  << "\n"
            << "\tend:    " << end    << "\n"
            << "\tcount:  " << count  << "\n";

  auto response_start  = std::chrono::system_clock::now();
  MsgPack result = do_visits_between(stop, start, end, count);
  auto response_end    = std::chrono::system_clock::now();
  std::chrono::duration<double, std::milli> elapsed_time = response_end - response_start;

  std::cout << "Responded in " << elapsed_time.count() << "ms with:\n"
            << result << "\n\n";

  return result;
}
