#pragma once

#include <map>
#include <vector>

namespace gtfs {
  enum class type {
    t_string,
    t_char,
    t_bool,
    t_int,
    t_float
  };

  using type_map_t = std::map<std::string, type>;

  template<typename T>
  class csv_parser {
    using object_list_t = std::vector<T>;

    type_map_t field_types = T::type_map;
    std::string file = T::file_name;

    public:
      csv_parser() = default;

  };
}
