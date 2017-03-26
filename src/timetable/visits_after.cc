#include "timetable.h"


MsgPack do_visits_after(std::string stop_code, DateTime start, int count) {
  (void) stop_code;
  (void) start;
  (void) count;
  return { };
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

