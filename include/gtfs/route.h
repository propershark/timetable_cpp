#pragma once

#include <ostream>
#include <sstream>

#include "modern_sqlite.h"

#include "gtfs/decls.h"


namespace GTFS {
  class Route : public ObjectBase<Route, std::string, std::string, std::string, std::string, std::string, std::string, std::string, std::string> {
    public:
      static std::string table_name;
      // Unique identifier for the route
      std::string id;
      // Identifier of the Agency that owns the route
      std::string agency_id;
      // Short, humanized identifier of the route
      std::string short_name;
      // Fully-humanized name of the route
      std::string long_name;
      // Description of the route's service
      std::string description;
      // Type of transportation used on the route
      std::string type;
      // Background color to use when displaying the route
      std::string color;
      // Text color to use when displaying the route
      std::string text_color;

      Route() = default;
      Route(std::string id, std::string agency, std::string sn, std::string ln, std::string desc, std::string type, std::string color, std::string text) : id(id), agency_id(agency), short_name(sn), long_name(ln), description(desc), type(type), color(color), text_color(text) {};


      // Standard stream output
      friend std::ostream& operator<<(std::ostream& os, const Route& r) {
        return os << "Route: \n"
          << "\tID: " << r.id << "\n"
          << "\tAgency: " << r.agency_id << "\n"
          << "\tShort Name: " << r.short_name << "\n"
          << "\tName: " << r.long_name << "\n"
          << "\tDescription: " << r.description << "\n"
          << "\tColor: " << r.color << "\n"
          << "\tText Color: " << r.text_color << "\n";
      };
  };

  std::string Route::table_name = "routes";
}
