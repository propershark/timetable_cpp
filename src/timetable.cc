#include <iostream>

#include "transport.h"
#include "modern_sqlite.h"
#include "gtfs.h"


void setup() {
  GTFS::use_db("data/citybus.db");

  // auto routes = GTFS::Route::where("route_short_name = '2A'");
  auto routes = GTFS::Route::all();
  for(auto&& route : routes)
    std::cout << route;

  GTFS::close_db();
}


int main() {
  Transport t("ws://shark-nyc1.transio.us:8080/ws");

  setup();

  t.subscribe("vehicles.4004", [](MPNode args, MPNode kwargs) {
    std::cout << "Received event: " << args << "\n";
  });
  t.start();

  return 0;
}
