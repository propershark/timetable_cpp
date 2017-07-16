#pragma once

#include <ostream>


namespace gtfs {
  class transfer {
    public:
      // Stop from which this transfer applies
      std::string from_stop_id;
      // Stop to which this transfer applies
      std::string to_stop_id;
      // Time at which service at this transfer ends
      int transfer_type;
      // Minimum transfer time (in seconds) allowed for a transfer
      int min_transfer_time;

      transfer() = default;

      void post_init() { };

      // Standard stream output
      friend std::ostream& operator<<(std::ostream& os, const transfer& t) {
        return os << "transfer: \n"
          << "\tFrom Stop: " << t.from_stop_id << "\n"
          << "\tTo Stop: " << t.to_stop_id << "\n"
          << "\tTransfer Type: " << t.transfer_type << "\n"
          << "\tMinimum Transfer Time: " << t.min_transfer_time << "\n";
      };
  };
}
