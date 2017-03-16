#pragma once

#include <ostream>

#include "gtfs/csv_parser.h"


namespace gtfs {
  class feed_info {
    public:
      static csv_parser<feed_info> parser;
      static std::string file_name;

      // Name of the entity publishing this feed
      std::string publisher_name;
      // URL for the publishing entity
      std::string publisher_url;
      // IETF BCP 47 Language code for the feed
      std::string language;
      // First date this feed is effective
      std::string start_date;
      // Last date this feed is effective
      std::string end_date;
      // Version number identifying this feed
      std::string version;

      feed_info() = default;


      // Standard stream output
      friend std::ostream& operator<<(std::ostream& os, const feed_info& fi) {
        return os << "feed_info: \n"
          << "\tPublisher Name: " << fi.publisher_name << "\n"
          << "\tPublisher URL: " << fi.publisher_url << "\n"
          << "\tLanguage: " << fi.language << "\n"
          << "\tStart Date: " << fi.start_date << "\n"
          << "\tEnd Date: " << fi.end_date << "\n"
          << "\tVersion: " << fi.version << "\n";
      };
  };

  std::string feed_info::file_name = "feed_info.txt";
  csv_parser<feed_info> feed_info::parser = {{
    { "feed_publisher_name", make_field_mapper(&feed_info::publisher_name) },
    { "feed_publisher_url",  make_field_mapper(&feed_info::publisher_url)  },
    { "feed_lang",           make_field_mapper(&feed_info::language)       },
    { "feed_start_date",     make_field_mapper(&feed_info::start_date)     },
    { "feed_end_date",       make_field_mapper(&feed_info::end_date)       },
    { "feed_version",        make_field_mapper(&feed_info::version)        }
  }};
}
