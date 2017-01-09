#pragma once

#include <ostream>

#include "gtfs/csv_parser.h"


namespace gtfs {
  class transfer {
    static csv_parser<transfer> parser;
    static type_map_t type_map;

    public:
      static std::string file_name;
      // Stop from which this transfer applies
      std::string from_stop_id;
      // Stop to which this transfer applies
      std::string to_stop_id;
      // Time at which service at this transfer ends
      int transfer_type;
      // Minimum transfer time (in seconds) allowed for a transfer
      int min_transfer_time;

      transfer() = default;


      // Standard stream output
      friend std::ostream& operator<<(std::ostream& os, const transfer& t) {
        return os << "transfer: \n"
          << "\tFrom Stop: " << t.from_stop_id << "\n"
          << "\tTo Stop: " << t.to_stop_id << "\n"
          << "\tTransfer Type: " << t.transfer_type << "\n"
          << "\tMinimum Transfer Time: " << t.min_transfer_time << "\n"
      };
  };

  std::string transfer::file_name = "transfers.txt";
  type_map_t transfer::type_map = {
    {"from_stop_id",      type::t_string},
    {"to_stop_id",        type::t_string},
    {"transfer_type",     type::t_int},
    {"min_transfer_time", type::t_int}
  };
}
