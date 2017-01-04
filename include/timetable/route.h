#pragma once

namespace Timetable {
  class Route {
    public:
      std::string id;
  };
}

template<>
struct std::hash<Timetable::Route> {
  std::size_t operator()(Timetable::Route& r) const {
    return std::hash<std::string>{}(r.id);
  }
};
