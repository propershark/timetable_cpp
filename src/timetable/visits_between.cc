#include "timetable.h"


namespace iteration_predicate {
  // An iteration predicate is any function that takes in the current date, a
  // visit_list_key, and a gtfs::stop_time and returns whether the current
  // iteration should continue.
  using type = std::function<bool(DateTime, Timetable::visit_list_key, gtfs::stop_time)>;

  class visits_before {
    DateTime end_dt;

    public:
      visits_before(DateTime end) : end_dt(end) {};

      bool operator()(DateTime date, Timetable::visit_list_key _key, gtfs::stop_time st) {
        (void) _key;
        auto visit_dt = date + DateTime::from_time(st.departure_time).without_date();
        return visit_dt <= end_dt;
      };
  };

  template<typename ...PREDICATES>
  class multi_predicate {
    std::vector<iteration_predicate::type> predicates;

    public:
      multi_predicate(PREDICATES&&... preds) : predicates(std::forward<PREDICATES>(preds)...) {};

      // Returns true iff all predicate conditions are met. If a predicate
      // fails, the function will return immediately, without evaluating the
      // remaining predicates.
      bool operator()(DateTime date, Timetable::visit_list_key key, gtfs::stop_time st) {
        for(auto pred : predicates) {
          if(!pred(date, key, st)) return false;
        }

        return true;
      };
  };
}


// An iterator_block is any function that takes a datetime, visit_list_key, and
// stop_time, performs some arbitrary operation, and returns whether iteration
// should continue.
using iterator_block = std::function<bool(DateTime, Timetable::visit_list_key, gtfs::stop_time)>;


void iterate_visits_at_station(std::string station_id, iteration_predicate::type predicate, iterator_block block) {
  DateTime current_date;
  for(auto pair : tt.visits_at_station(station_id)) {
    if( !(predicate(current_date, pair.first, pair.second) &&
          block(current_date, pair.first, pair.second))
      )
      break;
  }
};


MsgPack do_visits_between(std::string stop_code, DateTime start, DateTime end, int count) {
  auto stop           = tt.stops[stop_code];
  auto visits_bounds  = tt.visits_at_station(stop.id);

  std::vector<Visit> results;
  DateTime current_date = start.without_time();
  while(current_date <= end) {
    for(auto pair : visits_bounds) {
      auto stop_time = pair.second;
      if(stop_time.stop_id != stop.id) goto finish;

      auto departure_dt = current_date + DateTime::from_time(stop_time.departure_time).without_date();
      if(departure_dt < start) continue;
      if(departure_dt > end)   goto finish;

      if(!tt.is_active(stop_time, current_date)) continue;

      results.push_back({stop_time, departure_dt, departure_dt, tt});
      if((int) results.size() >= count) goto finish;
    }

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
