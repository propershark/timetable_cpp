#pragma once

#include <ostream>


namespace gtfs {
  class fare_rule {
    public:
      // Identifier for the fare this rule affect
      std::string fare_id;
      // Route this fare rule affects
      std::string route_id;
      // Fare zone from which this rule applies
      std::string origin_id;
      // Fare zone to which this rule applies
      std::string destination_id;
      // Fare zone that an itinerary must pass through for this rule to apply
      std::string contains_id;

      fare_rule() = default;


      // Standard stream output
      friend std::ostream& operator<<(std::ostream& os, const fare_rule& fr) {
        return os << "fare_rule: \n"
          << "\tFare: " << fr.fare_id << "\n"
          << "\troute_id: " << fr.route_id << "\n"
          << "\torigin_id: " << fr.origin_id << "\n"
          << "\tdestination_id: " << fr.destination_id << "\n"
          << "\tcontains_id: " << fr.contains_id << "\n";
      };
  };
}
