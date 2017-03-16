#pragma once

#include "mpackCPP/MsgPack.h"
#include "mpackCPP/MsgUnpack.h"
#include "gtfs.h"
#include "timetable.h"

class Visit {
  public:
    // Arrival time of the vehicle to this visit
    DateTime          arrival;
    // Departure time of the vehicle from this visit
    DateTime          departure;
    // Direct reference to this visit's gtfs attributes
    gtfs::stop_time&  stop_time;
    gtfs::stop&       station;
    gtfs::trip&       trip;
    gtfs::route&      route;

    Visit(gtfs::stop_time& st, std::string arrival_date, std::string departure_date, Timetable::Timetable& tt) :
        stop_time(st),
        station(tt.stops[stop_time.stop_id]),
        trip(tt.trips[stop_time.trip_id]),
        route(tt.routes[trip.route_id]) {
      arrival   = { arrival_date,   stop_time.arrival_time    };
      departure = { departure_date, stop_time.departure_time  };
    };

    // The headsign displayed on the vehicle making this visit. This can be set
    // on any of the route, trip, or stop_time, with each taking priority in
    // that order.
    // Routes do not have an exact `headsign` property, so if no other headsign
    // is provided, the route description is used instead.
    std::string headsign() {
      if(stop_time.headsign != "")  return stop_time.headsign;
      if(trip.headsign != "")       return trip.headsign;
                                    return route.description;
    };

    operator MsgPack() { return MsgPackArr{ arrival.to_string(), departure.to_string(), route.short_name, headsign() }; };
};
