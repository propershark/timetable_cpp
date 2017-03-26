#include "timetable.h"

#include "gtfs.h"

void create_indices() {
  tt.add_index("station.departure", [](auto stid, auto st) -> std::string {
    auto trip = tt.trips[st.trip_id];
    std::string key = st.stop_id + st.departure_time;
    key += stid;
    return key;
  });

  tt.add_index("route.station.departure", [](auto stid, auto st) -> std::string {
    auto trip = tt.trips[st.trip_id];
    std::string key = trip.route_id + st.stop_id + st.departure_time;
    key += stid;
    return key;
  });
};
