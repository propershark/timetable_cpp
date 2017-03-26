#include "timetable.h"


MsgPack do_visits_between_from_route(std::string stop_code, DateTime start, DateTime end, std::string route_name, int count) {
  (void) stop_code;
  (void) start;
  (void) end;
  (void) route_name;
  (void) count;
  return { };
}


MsgPack visits_between_from_route(std::string stop, std::string start, std::string end, std::string route_name, int count) {
  std::cout << "Received call to `visits_between_from_route`: \n"
            << "\tstop:   " << stop << "\n"
            << "\tstart:  " << start << "\n"
            << "\tend:    " << end << "\n"
            << "\troute:  " << route_name << "\n"
            << "\tcount:  " << count << "\n";

  auto response_start  = std::chrono::system_clock::now();
  MsgPack result = do_visits_between_from_route(stop, start, end, route_name, count);
  auto response_end    = std::chrono::system_clock::now();
  std::chrono::duration<double, std::milli> elapsed_time = response_end - response_start;

  std::cout << "Responded in " << elapsed_time.count() << "ms with:\n"
            << result << "\n\n";

  return result;
}

