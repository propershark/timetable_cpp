#pragma once

#include <ostream>


namespace gtfs {
  class fare_attribute {
    public:
      // Identifier for the fare these attributes affect
      std::string fare_id;
      // Price of the fare
      std::string price;
      // ISO4217 code for the currency of the fare price
      std::string currency_type;
      // Indiciation of when the fare must be paid
      int payment_method;
      // Number of transfers allowed with this fare
      int transfers;
      // Length of time (in seconds) that transfers are possible
      int transfer_duration;

      fare_attribute() = default;


      // Standard stream output
      friend std::ostream& operator<<(std::ostream& os, const fare_attribute& fa) {
        return os << "fare_attribute: \n"
          << "\tFare: " << fa.fare_id << "\n"
          << "\tPrice: " << fa.price << "\n"
          << "\tCurrency: " << fa.currency_type << "\n"
          << "\tPayment Method: " << fa.payment_method << "\n"
          << "\tTransfers: " << fa.transfers << "\n"
          << "\tTransfer Duration: " << fa.transfer_duration << "\n";
      };
  };
}
