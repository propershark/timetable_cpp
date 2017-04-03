#include <iostream>
#include <sstream>
#include <vector>

#include "timetable.h"
#include "transport.h"


Timetable::Timetable tt("data/citybus");


int main() {
  Transport t("ws://shark-nyc1.transio.us:8080/ws");

  create_indices();
  tt.initialize();

  t.procedure("timetable.visits_before",              visits_before);
  t.procedure("timetable.visits_before_from_route",   visits_before_from_route);
  t.procedure("timetable.visits_between",             visits_between);
  t.procedure("timetable.visits_between_from_route",  visits_between_from_route);
  t.procedure("timetable.visits_after",               visits_after);
  t.procedure("timetable.visits_after_from_route",    visits_after_from_route);
  t.start();

  return 0;
}
