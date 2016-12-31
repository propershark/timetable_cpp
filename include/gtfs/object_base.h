#pragma once

#include <sstream>
#include <cxxabi.h>

#include "builder.h"


namespace GTFS {
  template<typename T, typename... AttrTypes>
  class ObjectBase {
    typedef Builder<T, AttrTypes...> builder_t;

    public:
      ObjectBase() = default;

      static std::vector<T> all() {
        std::stringstream query;
        query << "SELECT * FROM " << T::table_name << ";";
        current_db() << query.str()
          >> object_builder();

        return object_builder().results();
      };

      template<typename... Args>
      static std::vector<T> where(std::string filter_str, Args... filter_binds) {
        std::stringstream query;
        query << "SELECT * FROM " << T::table_name << " WHERE (" << filter_str << ");";
        (current_db() << query.str() << ... << filter_binds)
        >> object_builder();

        return object_builder().results();
      };

      static const std::string& class_name() {
        static int status;
        static std::string class_name;
        if(class_name.empty()) {
          class_name = abi::__cxa_demangle(typeid(T).name(), 0, 0, &status);
          class_name = class_name.substr(class_name.rfind("::")+2);
        }
        return class_name;
      }

    private:
      static builder_t& object_builder() {
        static builder_t builder;
        return builder;
      };
  };
}
