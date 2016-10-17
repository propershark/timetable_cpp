#pragma once

#include "gtfs/decls.h"


namespace GTFS {
  template<typename Target, typename... AttrTypes>
  class Builder {
    std::vector<Target> result_list;

    public:
      Builder() = default;

      void operator()(AttrTypes... args) {
        result_list.emplace_back(std::forward<AttrTypes&&>(args)...);
      }

      void reset() {
        result_list.empty();
      }

      std::vector<Target> results() {
        return result_list;
      }
  };
}
