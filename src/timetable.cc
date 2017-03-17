#include <iostream>
#include <sstream>
#include <vector>

#include "timetable.h"
#include "transport.h"


Timetable::Timetable tt("data/citybus");


int main() {
  Transport t("ws://shark-nyc1.transio.us:8080/ws");

  t.procedure("timetable.visits_between",             visits_between);
  t.procedure("timetable.visits_between_from_route",  visits_between_from_route);
  t.start();

  // visits_between("BUS389", "20170130 06:44:00", "20170130 10:44:00", 2);
  // visits_between("BUS389", "20170130 06:44:00", "20170130 10:44:00", 10);

  return 0;
}
