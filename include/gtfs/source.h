#pragma once

#include "gtfs/field_mapper.h"
#include "gtfs/csv_parser.h"

namespace gtfs {
  class source {
    // The path to the directory containing GTFS archive files. All file names
    // are expected to be the snake-cased plural of the object type followed by
    // `.txt` (e.g., `stop_times.txt`, `routes.txt`), with the exception of
    // `agency.txt`, `calendar.txt`, and `feed_info.txt`.
    std::string directory;

    template<typename T>
    using field_map_t = std::map<std::string, field_mapper<T>>;

    public:
      // Field maps for each type defined by GTFS.
      field_map_t<agency> agency_fields = {
        { "agency_id",        make_field_mapper(&agency::id)       },
        { "agency_name",      make_field_mapper(&agency::name)     },
        { "agency_url",       make_field_mapper(&agency::url)      },
        { "agency_timezone",  make_field_mapper(&agency::timezone) },
        { "agency_lang",      make_field_mapper(&agency::language) },
        { "agency_phone",     make_field_mapper(&agency::phone)    },
        { "agency_fare_url",  make_field_mapper(&agency::fare_url) },
        { "agency_email",     make_field_mapper(&agency::email)    }
      };

      field_map_t<calendar> calendar_fields = {
        { "service_id",  make_field_mapper(&calendar::service_id)  },
        { "monday",      make_field_mapper(&calendar::monday)      },
        { "tuesday",     make_field_mapper(&calendar::tuesday)     },
        { "wednesday",   make_field_mapper(&calendar::wednesday)   },
        { "thursday",    make_field_mapper(&calendar::thursday)    },
        { "friday",      make_field_mapper(&calendar::friday)      },
        { "saturday",    make_field_mapper(&calendar::saturday)    },
        { "sunday",      make_field_mapper(&calendar::sunday)      },
        { "start_date",  make_field_mapper(&calendar::start_date)  },
        { "end_date",    make_field_mapper(&calendar::end_date)    }
      };

      field_map_t<calendar_date> calendar_date_fields = {
        { "service_id",     make_field_mapper(&calendar_date::service_id)     },
        { "date",           make_field_mapper(&calendar_date::date)           },
        { "exception_type", make_field_mapper(&calendar_date::exception_type) }
      };

      field_map_t<fare_attribute> fare_attribute_fields = {
        { "fare_id",           make_field_mapper(&fare_attribute::fare_id)           },
        { "price",             make_field_mapper(&fare_attribute::price)             },
        { "currency_type",     make_field_mapper(&fare_attribute::currency_type)     },
        { "payment_method",    make_field_mapper(&fare_attribute::payment_method)    },
        { "transfers",         make_field_mapper(&fare_attribute::transfers)         },
        { "transfer_duration", make_field_mapper(&fare_attribute::transfer_duration) },
      };

      field_map_t<fare_rule> fare_rule_fields = {
        { "fare_id",         make_field_mapper(&fare_rule::fare_id)        },
        { "route_id",        make_field_mapper(&fare_rule::route_id)       },
        { "origin_id",       make_field_mapper(&fare_rule::origin_id)      },
        { "destination_id",  make_field_mapper(&fare_rule::destination_id) },
        { "contains_id",     make_field_mapper(&fare_rule::contains_id)    }
      };

      field_map_t<feed_info> feed_info_fields = {
        { "feed_publisher_name", make_field_mapper(&feed_info::publisher_name) },
        { "feed_publisher_url",  make_field_mapper(&feed_info::publisher_url)  },
        { "feed_lang",           make_field_mapper(&feed_info::language)       },
        { "feed_start_date",     make_field_mapper(&feed_info::start_date)     },
        { "feed_end_date",       make_field_mapper(&feed_info::end_date)       },
        { "feed_version",        make_field_mapper(&feed_info::version)        }
      };

      field_map_t<frequency> frequency_fields = {
        { "trip_id",       make_field_mapper(&frequency::trip_id)            },
        { "start_time",    make_field_mapper(&frequency::start_time)         },
        { "end_time",      make_field_mapper(&frequency::end_time)           },
        { "headway_secs",  make_field_mapper(&frequency::headway)            },
        { "exact_times",   make_field_mapper(&frequency::exact_times, false) }
      };

      field_map_t<route> route_fields = {
        { "route_id",         make_field_mapper(&route::id)           },
        { "agency_id",        make_field_mapper(&route::agency_id)    },
        { "route_short_name", make_field_mapper(&route::short_name)   },
        { "route_long_name",  make_field_mapper(&route::long_name)    },
        { "route_desc",       make_field_mapper(&route::description)  },
        { "route_url",        make_field_mapper(&route::url)          },
        { "route_type",       make_field_mapper(&route::type)         },
        { "route_color",      make_field_mapper(&route::color)        },
        { "route_text_color", make_field_mapper(&route::text_color)   }
      };

      field_map_t<shape> shape_fields = {
        { "shape_id",            make_field_mapper(&shape::id)         },
        { "shape_pt_lat",        make_field_mapper(&shape::latitude)   },
        { "shape_pt_lon",        make_field_mapper(&shape::longitude)  },
        { "shape_pt_sequence",   make_field_mapper(&shape::index)      },
        { "shape_dist_traveled", make_field_mapper(&shape::distance)   }
      };

      field_map_t<stop> stop_fields = {
        { "stop_id",             make_field_mapper(&stop::id)                     },
        { "stop_code",           make_field_mapper(&stop::code)                   },
        { "stop_name",           make_field_mapper(&stop::name)                   },
        { "stop_desc",           make_field_mapper(&stop::description)            },
        { "stop_lat",            make_field_mapper(&stop::latitude)               },
        { "stop_lon",            make_field_mapper(&stop::longitude)              },
        { "zone_id",             make_field_mapper(&stop::zone_id)                },
        { "stop_url",            make_field_mapper(&stop::stop_url)               },
        { "location_type",       make_field_mapper(&stop::type, 0)                },
        { "parent_station",      make_field_mapper(&stop::parent_id)              },
        { "stop_timezone",       make_field_mapper(&stop::timezone)               },
        { "wheelchair_boarding", make_field_mapper(&stop::wheelchair_boarding, 0) }
      };

      field_map_t<stop_time> stop_time_fields = {
        { "trip_id",             make_field_mapper(&stop_time::trip_id)         },
        { "arrival_time",        make_field_mapper(&stop_time::arrival_time)    },
        { "departure_time",      make_field_mapper(&stop_time::departure_time)  },
        { "stop_id",             make_field_mapper(&stop_time::stop_id)         },
        { "stop_sequence",       make_field_mapper(&stop_time::index)           },
        { "stop_headsign",       make_field_mapper(&stop_time::headsign)        },
        { "pickup_type",         make_field_mapper(&stop_time::pickup_type, 0)  },
        { "drop_off_type",       make_field_mapper(&stop_time::dropoff_type, 0) },
        { "shape_dist_traveled", make_field_mapper(&stop_time::distance)        },
        { "timepoint",           make_field_mapper(&stop_time::timepoint, true) }
      };

      field_map_t<transfer> transfer_fields = {
        { "from_stop_id",      make_field_mapper(&transfer::from_stop_id)       },
        { "to_stop_id",        make_field_mapper(&transfer::to_stop_id)         },
        { "transfer_type",     make_field_mapper(&transfer::transfer_type)      },
        { "min_transfer_time", make_field_mapper(&transfer::min_transfer_time)  }
      };

      field_map_t<trip> trip_fields {
        { "route_id",              make_field_mapper(&trip::route_id)                 },
        { "service_id",            make_field_mapper(&trip::service_id)               },
        { "trip_id",               make_field_mapper(&trip::id)                       },
        { "trip_headsign",         make_field_mapper(&trip::headsign)                 },
        { "trip_short_name",       make_field_mapper(&trip::short_name)               },
        { "direction_id",          make_field_mapper(&trip::direction_id)             },
        { "block_id",              make_field_mapper(&trip::block_id)                 },
        { "shape_id",              make_field_mapper(&trip::shape_id)                 },
        { "wheelchair_accessible", make_field_mapper(&trip::wheelchair_accessible, 0) },
        { "bikes_allowed",         make_field_mapper(&trip::bikes_allowed, 0)         }
      };

      // Parser objects for each type defined by GTFS.
      csv_parser<agency> agency_parser;
      csv_parser<calendar> calendar_parser;
      csv_parser<calendar_date> calendar_date_parser;
      csv_parser<fare_attribute> fare_attribute_parser;
      csv_parser<fare_rule> fare_rule_parser;
      csv_parser<feed_info> feed_info_parser;
      csv_parser<frequency> frequency_parser;
      csv_parser<route> route_parser;
      csv_parser<shape> shape_parser;
      csv_parser<stop> stop_parser;
      csv_parser<stop_time> stop_time_parser;
      csv_parser<transfer> transfer_parser;
      csv_parser<trip> trip_parser;


      source(std::string directory) : directory(directory) {
        agency_parser         = { directory + "/agency.txt",          agency_fields };
        calendar_parser       = { directory + "/calendar.txt",        calendar_fields };
        calendar_date_parser  = { directory + "/calendar_dates.txt",  calendar_date_fields };
        fare_attribute_parser = { directory + "/fare_attributes.txt", fare_attribute_fields };
        fare_rule_parser      = { directory + "/fare_rules.txt",      fare_rule_fields };
        feed_info_parser      = { directory + "/feed_info.txt",       feed_info_fields };
        frequency_parser      = { directory + "/frequencies.txt",     frequency_fields };
        route_parser          = { directory + "/routes.txt",          route_fields };
        shape_parser          = { directory + "/shapes.txt",          shape_fields };
        stop_parser           = { directory + "/stops.txt",           stop_fields };
        stop_time_parser      = { directory + "/stop_times.txt",      stop_time_fields };
        transfer_parser       = { directory + "/transfers.txt",       transfer_fields };
        trip_parser           = { directory + "/trips.txt",           trip_fields };
      };
  };
}
