#pragma once

#include <map>

#include "gtfs.h"


namespace Timetable {
  class index : public std::map<std::string, gtfs::stop_time*> {
    public:
      using indexer = std::function<std::string(unsigned long, gtfs::stop_time&)>;

      indexer make_index;


      index() {};
      index(indexer func) : make_index(func) {};


      void add_entry(unsigned long stid, gtfs::stop_time& st) {
        (*this)[make_index(stid, st)] = &st;
      };
  };
}
