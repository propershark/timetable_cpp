#pragma once

#include <ostream>

#include "gtfs/csv_parser.h"


namespace gtfs {
  class fare_attribute {
    static csv_parser<fare_attribute> parser;
    static type_map_t type_map;

    public:
      static std::string file_name;
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

  std::string fare_attribute::file_name = "fare_attributes.txt";
  type_map_t fare_attribute::type_map = {
    {"fare_id",           type::t_string},
    {"price",             type::t_string},
    {"currency_type",     type::t_string},
    {"payment_method",    type::t_int},
    {"transfers",         type::t_int},
    {"transfer_duration", type::t_int}
  };
}
