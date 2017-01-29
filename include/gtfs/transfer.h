#pragma once

#include <ostream>

#include "gtfs/csv_parser.h"


namespace gtfs {
  class transfer {
    public:
      static csv_parser<transfer> parser;
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
          << "\tMinimum Transfer Time: " << t.min_transfer_time << "\n";
      };
  };

  std::string transfer::file_name = "transfers.txt";
  csv_parser<transfer> transfer::parser = {{
    { "from_stop_id",      make_field_mapper(&transfer::from_stop_id)       },
    { "to_stop_id",        make_field_mapper(&transfer::to_stop_id)         },
    { "transfer_type",     make_field_mapper(&transfer::transfer_type)      },
    { "min_transfer_time", make_field_mapper(&transfer::min_transfer_time)  }
  }};
}