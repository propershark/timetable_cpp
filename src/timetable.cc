#include <iostream>
#include <sstream>
#include <unistd.h>
#include <vector>

#include "timetable.h"
#include "transport.h"


Timetable::Timetable *tt;

static void abort_usage() {
  std::cerr << "usage: timetable [-t transport_address] gtfs_directory\n";
  exit(1);
};

int main(int argc, char * const argv[]) {
  int ch;
  std::string transport_address;
  std::string gtfs_dir;
  do {
    ch = getopt(argc, argv, "-t:");
    switch (ch) {
      case 't': transport_address = optarg;
                break;

                // Detect gtfs_dir on linux.
      case 1:   gtfs_dir = optarg;
                break;

                // Detect gtfs_dir on POSIX.
      case -1:  if (optind < argc) gtfs_dir = argv[optind];
                break;

      default:  break;
    }
  } while (ch != -1);

  if (transport_address.empty())
    transport_address = "ws://localhost:8080/ws";
  if (gtfs_dir.empty())
    abort_usage();

  tt = new Timetable::Timetable(gtfs_dir);
  Transport t(transport_address);

  create_indices();
  tt->initialize();

  t.procedure("timetable.visits_before",              visits_before);
  t.procedure("timetable.visits_before_from_route",   visits_before_from_route);
  t.procedure("timetable.visits_between",             visits_between);
  t.procedure("timetable.visits_between_from_route",  visits_between_from_route);
  t.procedure("timetable.visits_after",               visits_after);
  t.procedure("timetable.visits_after_from_route",    visits_after_from_route);
  t.start();

  return 0;
}
