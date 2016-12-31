#pragma once

class Visit {
  public:
    // Arrival time of the vehicle to this visit
    std::string arrival;
    // Departure time of the vehicle from this visit
    std::string departure;

    Visit(std::string arv, std::string dpt) : arrival(arv), departure(dpt) {};

    operator MsgPack() {
      return MsgPackArr(*this);
    }

    operator MsgPackArr() {
      return { arrival, departure };
    }
};
