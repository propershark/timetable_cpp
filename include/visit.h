#pragma once

#include "gtfs.h"

class Visit {
  public:
    // Arrival time of the vehicle to this visit
    std::string arrival;
    // Departure time of the vehicle from this visit
    std::string departure;

    Visit(std::string arv, std::string dpt) : arrival(arv), departure(dpt) {};
    Visit(gtfs::stop_time st) : arrival(st.arrival_time), departure(st.departure_time) {};

    operator MsgPack() {
      return MsgPackArr(*this);
    }

    operator MsgPackArr() {
      return { arrival, departure };
    }
};
