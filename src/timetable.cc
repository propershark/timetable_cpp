#include <iostream>
#include <sstream>

#include "datetime.h"
#include "transport.h"
#include "modern_sqlite.h"
#include "gtfs.h"
#include "visit.h"


void setup() {
  GTFS::use_db("data/citybus.db");

  GTFS::close_db();
}


int next_visits(std::string arg1, std::string arg2, DateTime timestamp, int count) {
  std::cout << "Got call request\n"
  << "Arg1 " << arg1 << "\n"
  << "Arg2 " << arg2 << "\n"
  << "Time " << timestamp << "\n"
  << "Count " << count << "\n";

  return 1;
}
int next_visit(std::string arg1, std::string arg2, DateTime ts) { return next_visits(arg1, arg2, ts, 1); }

int last_visits(std::string arg1, std::string arg2, DateTime timestamp, int count) {
  std::cout << "Got call request\n"
  << "Arg1 " << arg1 << "\n"
  << "Arg2 " << arg2 << "\n"
  << "Time " << timestamp << "\n"
  << "Count " << count << "\n";

  return 1;
}
int last_visit(std::string arg1, std::string arg2, DateTime ts) { return last_visits(arg1, arg2, ts, 1); }


int main() {
  Transport t("ws://shark-nyc1.transio.us:8080/ws");

  GTFS::use_db("data/citybus.db");
  setup();

  t.procedure("timetable.next_visit",   next_visit);
  t.procedure("timetable.next_visits",  next_visits);
  t.procedure("timetable.last_visit",   last_visit);
  t.procedure("timetable.last_visits",  last_visits);
  t.start();

  GTFS::close_db();

  return 0;
}
