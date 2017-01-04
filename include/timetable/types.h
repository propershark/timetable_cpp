#pragma once

namespace Timetable {
  class Route {
    public:
      std::string id;
      std::string name;
      std::string short_name;

      Route() = default;
      Route(std::string id) : id(id) {};

      bool operator ==(const Route other) const { return id == other.id; };
  };

  class Trip {
    public:
      std::string id;
      std::string start_time;
      std::string end_time;
      Route route;

      Trip() = default;
      Trip(std::string id) : id(id) {};

      bool operator ==(const Trip other) const { return id == other.id; };
  };

  class Stop {
    public:
      std::string id;
      std::string code;
      std::string name;
      std::string desc;

      Stop() = default;
      Stop(std::string id) : id(id) {};

      bool operator ==(const Stop other) const { return id == other.id; };
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

      bool operator ==(const Visit other) const {
        return trip           == other.trip
            && arrival        == other.arrival
            && departure      == other.departure
            && stop           == other.stop
            && index          == other.index
            && pickup_type    == other.pickup_type
            && dropoff_type   == other.dropoff_type
            && dist_traveled  == other.dist_traveled;
      };
  };
}


template<>
struct std::hash<Timetable::Route> {
  std::size_t operator()(Timetable::Route r) { return std::hash<std::string>{}(r.id); };
};

// template<>
// struct std::hash<Timetable::Trip> {
//   std::size_t operator()(Timetable::Trip t) { return std::hash<std::string>{}(t.id); };
// };

template<>
struct std::hash<Timetable::Stop> {
  std::size_t operator()(Timetable::Stop s) { return std::hash<std::string>{}(s.id); };
};
