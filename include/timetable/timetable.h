#pragma once

#include <map>
#include <unordered_map>

#include "gtfs.h"
#include "timetable/calendar.h"

namespace Timetable {
  class Timetable {
    // Map of trip IDs to their full objects
    using trip_map_t  = std::unordered_map<std::string, gtfs::trip>;
    // Map of stop_times ordered by stop index
    using trip_visit_list_t = std::map<int, gtfs::stop_time>;

    public:
      std::string archive_dir;

      trip_map_t  trip_map;
      Calendar    calendar;
      visit_list  visits;
      std::unordered_map<std::string, trip_visit_list_t> visits_by_trip;


      Timetable(std::string directory) : archive_dir(directory), calendar(directory) {
        std::cout << "Reading trips\n";
        auto trips = gtfs::trip::parser.all(archive_dir);
        for(auto trip : trips) trip_map[trip.id] = trip;

        std::cout << "Parsing stop times\n";
        _parse_stop_times();
        std::cout << "Interpolating departures\n";
        _interpolate_stop_time_departures();
        std::cout << "Done\n";
      };


      inline void add_visit(gtfs::stop_time visit) {
        visits[_make_visit_list_key(visit)] = visit;
      };


      inline bool is_active(gtfs::stop_time visit, std::string date) {
        auto trip = trip_map[visit.trip_id];
        return calendar.service_is_active(trip.service_id, date);
      };


      ////
      // Views
      ////

      reverse_bounds_t visits_before(const visit_list_key key) const {
        auto lower_bound = visits.lower_bound(key.station_lower_bound());
        auto upper_bound = visits.upper_bound(key);
        bounds_t bounds{ lower_bound, upper_bound };
        return reverse(bounds);
      };

      bounds_t visits_between(const visit_list_key key1, const visit_list_key key2) const {
        return { visits.lower_bound(key1), visits.upper_bound(key2) };
      };

      bounds_t visits_after(const visit_list_key key) const {
        auto lower_bound = visits.lower_bound(key);
        auto upper_bound = visits.upper_bound(key.station_upper_bound());
        return { lower_bound, upper_bound };
      };



    private:
      void _parse_stop_times() {
        auto& parser = gtfs::stop_time::parser;
        parser.initialize(archive_dir);
        while(parser.has_next()) {
          auto stop_time = parser.next();
          visits_by_trip[stop_time.trip_id].insert({ stop_time.index, stop_time });
        }
        parser.finish();
      };

      void _interpolate_stop_time_departures() {
        for(auto&& pair : visits_by_trip) {
          auto& visit_list = pair.second;
          gtfs::stop_time last_timepoint;
          gtfs::stop_time next_timepoint;
          double timepoint_distance = 0;

          for(auto it = visit_list.begin(); it != visit_list.end(); ++it) {
            auto& visit = it->second;
            // If this visit is a timepoint, use it as the "preceding timed
            // stop" for future visits, and locate the timepoint to use for
            // next_timepoint.
            if(visit.departure_time != "") {
              last_timepoint = visit;
              for(auto next = it; next != visit_list.end(); ++next) {
                auto& next_visit = next->second;
                if(next_visit.departure_time != "") {
                  next_timepoint = next_visit;
                  break;
                }
              }

              timepoint_distance = next_timepoint.distance - last_timepoint.distance;
            } else {
              // auto percent_traveled = visit.distance / timepoint_distance;
              // visit.departure_time = last_timepoint.departure_time + percent_traveled;
              visit.departure_time = last_timepoint.departure_time;
            }

            add_visit(visit);
          }
        }
      };


      inline visit_list_key _make_visit_list_key(gtfs::stop_time st) {
        auto trip = trip_map[st.trip_id];
        return visit_list_key(st.stop_id, trip.route_id, st.trip_id, st.departure_time);
      };
  };
}
