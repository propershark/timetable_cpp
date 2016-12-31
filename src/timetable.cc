#include <iostream>

#include "transport.h"
#include "modern_sqlite.h"
#include "gtfs.h"
#include "visit.h"


void setup() {
  GTFS::use_db("data/citybus.db");

  auto routes = GTFS::Route::where("route_short_name = ? OR route_short_name = ?", std::string("4B"), std::string("1A"));
  for(auto&& route : routes)
    std::cout << route;

  GTFS::close_db();
}

Visit next_visits() {
  std::cout << "Got call request\n";
  return { "first", "second" };
}

int main() {
  Transport t("ws://shark-nyc1.transio.us:8080/ws");

  // GTFS::use_db("data/citybus.db");
  setup();

  // t.procedure("timetable.next_visits", next_visits);
  // t.start();

  // GTFS::close_db();

  return 0;
}
