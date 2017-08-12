#pragma once

#include <algorithm>
#include <chrono>
#include <iostream>
#include <map>
#include <unordered_map>

#include "datetime.h"
#include "gtfs.h"
#include "timetable/calendar.h"
#include "timetable/index.h"

namespace Timetable {
  inline std::string next(std::string arg) { std::string tmp = arg; tmp.back()++; return tmp; };
  inline std::string prev(std::string arg) { std::string tmp = arg; tmp.back()--; return tmp; };

  class Timetable {
    public:
      std::string   directory;
      gtfs::source  source;
      Calendar      calendar;

      std::unordered_map<std::string, gtfs::trip>   trips;
      std::unordered_map<std::string, gtfs::route>  routes;
      std::unordered_map<std::string, gtfs::route>  routes_by_short_name;
      std::unordered_map<std::string, gtfs::stop>   stops;
      std::unordered_map<std::string, std::map<int, gtfs::stop_time>> visits_by_trip;

      std::vector<gtfs::stop_time>                  stop_times;
      std::map<std::string, index>                  st_indices;


      Timetable(std::string directory) : directory(directory), source(directory), calendar(source) {};

      void initialize() {
        std::cout << "Reading trips\n";
        for(auto trip : source.trip_parser.all()) trips[trip.id] = trip;
        std::cout << "Reading routes\n";
        for(auto route : source.route_parser.all()) {
          routes[route.id] = route;
          routes_by_short_name[route.short_name] = route;
        }
        std::cout << "Reading stops\n";
        for(auto stop : source.stop_parser.all()) stops[stop.code] = stop;

        std::cout << "Parsing stop times\n";
        _parse_stop_times();
        std::cout << "Interpolating departures\n";
        _interpolate_stop_time_departures();
        std::cout << "Done\n";

        std::cout << "Building indices\n";
        _build_indices();
      };


      inline void add_visit(gtfs::stop_time st) {
        stop_times.push_back(st);
      };

      inline bool is_active(gtfs::stop_time st, DateTime date) {
        auto trip = trips[st.trip_id];
        return calendar.service_is_active(trip.service_id, date);
      };


      ////
      // Indexing
      ////

      void add_index(std::string index_name, index::indexer idx) {
        st_indices.try_emplace(index_name, idx);
      }


    private:
      void _parse_stop_times() {
        source.stop_time_parser.initialize();
        while(source.stop_time_parser.has_next()) {
          auto stop_time = source.stop_time_parser.next();
          visits_by_trip[stop_time.trip_id].insert({ stop_time.index, stop_time });
        }
        source.stop_time_parser.finish();
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
              visit.arrival_time = last_timepoint.arrival_time;
            }

            add_visit(visit);
          }
        }
      };

      void _build_indices() {
        for(unsigned long st_index = 0; st_index < stop_times.size(); st_index++) {
          for(auto& pair : st_indices) {
            auto& idx = pair.second;
            idx.add_entry(st_index, stop_times[st_index]);
          }
        }
      };


      inline visit_list_key _make_visit_list_key(gtfs::stop_time st) {
        auto trip = trips[st.trip_id];
        return visit_list_key(st.stop_id, DateTime::from_time(st.departure_time), trip.route_id, st.trip_id);
      };
  };
}
