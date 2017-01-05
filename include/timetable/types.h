#pragma once

namespace Timetable {
  class Route {
    public:
      std::string id;
      std::string name;
      std::string short_name;

      Route() = default;
      Route(std::string id) : id(id) {};

      Route inc() const { Route temp = *this; temp.id += "a"; return temp; };

      friend bool operator ==(const Route& a, const Route& b) { return a.id == b.id; };
      friend bool operator !=(const Route& a, const Route& b) { return !(a == b); };
  };

  class Trip {
    public:
      std::string id;
      std::string start_time;
      std::string end_time;
      Route route;

      Trip() = default;
      Trip(std::string id) : id(id) {};

      Trip inc() const { Trip temp = *this; temp.id += "a"; return temp; };

      friend bool operator ==(const Trip& a, const Trip& b) { return a.id == b.id; };
      friend bool operator !=(const Trip& a, const Trip& b) { return !(a == b); };
  };

  class Stop {
    public:
      std::string id;
      std::string code;
      std::string name;
      std::string desc;

      Stop() = default;
      Stop(std::string id) : id(id) {};

      friend bool operator ==(const Stop& a, const Stop& b) { return a.id == b.id; };
      friend bool operator !=(const Stop& a, const Stop& b) { return !(a == b); };
  };

  class Visit {
    public:
      Trip trip;
      std::string arrival;
      std::string departure;
      Stop stop;
      int index;
      int pickup_type;
      int dropoff_type;
      float dist_traveled;

      Visit() = default;
      Visit(Trip t, std::string departure) : trip(t), departure(departure) {};

      friend bool operator ==(const Visit& a, const Visit& b) {
        return a.trip           == b.trip
            && a.arrival        == b.arrival
            && a.departure      == b.departure
            && a.stop           == b.stop
            && a.index          == b.index
            && a.pickup_type    == b.pickup_type
            && a.dropoff_type   == b.dropoff_type
            && a.dist_traveled  == b.dist_traveled;
      };
      friend bool operator !=(const Visit& a, const Visit& b) { return !(a == b); };
  };
}
