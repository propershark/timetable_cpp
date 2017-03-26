#include "timetable.h"


MsgPack do_visits_after_from_route(std::string stop_code, DateTime start, std::string route_name, int count) {
  (void) stop_code;
  (void) start;
  (void) route_name;
  (void) count;
  return { };
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

