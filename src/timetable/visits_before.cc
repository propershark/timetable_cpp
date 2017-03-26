#include "timetable.h"


MsgPack do_visits_before(std::string stop_code, DateTime end, int count) {
  (void) stop_code;
  (void) end;
  (void) count;
  return { };
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
