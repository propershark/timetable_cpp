#pragma once

namespace Timetable {
  class Route {
    public:
      std::string id;
      std::string name;
      std::string short_name;

      Route() = default;
      Route(std::string id) : id(id) {};

      friend bool operator ==(const Route& a, const Route& b) { return a.id == b.id; };
      friend bool operator !=(const Route& a, const Route& b) { return !(a == b); };
  };

  class Trip {
    public:
      std::string id;
      std::string route_id;
      std::string start_time;
      std::string end_time;

      Trip(std::string route, std::string id) : route_id(route), id(id) {};

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

      friend bool operator ==(Stop& a, Stop& b) { return a.id == b.id; };
      friend bool operator !=(Stop& a, Stop& b) { return !(a == b); };
  };

  class Visit {
    public:
      std::string route_id;
      std::string trip_id;
      std::string stop_id;
      std::string arrival;
      std::string departure;
      int         index;
      int         pickup_type;
      int         dropoff_type;
      float       dist_traveled;

      Visit() = default;
      Visit(std::string route, std::string trip, std::string stop, std::string depart) : route_id(route), trip_id(trip), stop_id(stop), departure(depart) {};

      friend bool operator ==(Visit& a, Visit& b) {
        return a.route_id       == b.route_id
            && a.trip_id        == b.trip_id
            && a.stop_id        == b.stop_id
            && a.arrival        == b.arrival
            && a.departure      == b.departure
            && a.index          == b.index
            && a.pickup_type    == b.pickup_type
            && a.dropoff_type   == b.dropoff_type
            && a.dist_traveled  == b.dist_traveled;
      };
      friend bool operator !=(Visit& a, Visit& b) { return !(a == b); };
  };
}
