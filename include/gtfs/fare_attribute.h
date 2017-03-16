#pragma once

#include <ostream>

#include "gtfs/csv_parser.h"


namespace gtfs {
  class fare_attribute {
    public:
      static csv_parser<fare_attribute> parser;
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
  csv_parser<fare_attribute> fare_attribute::parser = {{
    { "fare_id",           make_field_mapper(&fare_attribute::fare_id)           },
    { "price",             make_field_mapper(&fare_attribute::price)             },
    { "currency_type",     make_field_mapper(&fare_attribute::currency_type)     },
    { "payment_method",    make_field_mapper(&fare_attribute::payment_method)    },
    { "transfers",         make_field_mapper(&fare_attribute::transfers)         },
    { "transfer_duration", make_field_mapper(&fare_attribute::transfer_duration) },
  }};
}
