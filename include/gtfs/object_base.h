#pragma once

#include <sstream>

#include "builder.h"

namespace GTFS {
  template<typename T, typename... AttrTypes>
  class ObjectBase {
    typedef Builder<T, AttrTypes...> builder_t;

    public:
      ObjectBase() = default;

      static std::vector<T> all() {
        builder_t object_builder{};
        std::stringstream query;
        query << "SELECT * FROM " << T::table_name << ";";
        current_db() << query.str()
          >> object_builder;

        return object_builder.results();
      };

      static std::vector<T> where(std::string filter) {
        builder_t object_builder{};
        std::stringstream query;
        query << "SELECT * FROM " << T::table_name << " WHERE (" << filter << ");";
        current_db() << query.str()
          >> object_builder;

        return object_builder.results();
      };
  };
}
