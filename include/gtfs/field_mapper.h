#pragma once

#include "gtfs/types.h"

namespace gtfs {
  template<class Class>
  struct field_mapper {
    bool        Class::*bool_target;
    std::string Class::*string_target;
    int         Class::*int_target;
    double      Class::*double_target;
    Type        type;

    explicit field_mapper() = default;
    explicit field_mapper(bool        Class::*member) : bool_target(member),    type(tBOOL)   {};
    explicit field_mapper(std::string Class::*member) : string_target(member),  type(tSTRING) {};
    explicit field_mapper(int         Class::*member) : int_target(member),     type(tINT)    {};
    explicit field_mapper(double      Class::*member) : double_target(member),  type(tDOUBLE) {};

    inline void apply(Class& inst, bool val)        const { inst.*bool_target   = val; };
    inline void apply(Class& inst, std::string val) const { inst.*string_target = val; };
    inline void apply(Class& inst, int val)         const { inst.*int_target    = val; };
    inline void apply(Class& inst, double val)      const { inst.*double_target  = val; };
  };

  template<class Class, typename ValueType>
  constexpr auto make_field_mapper(ValueType Class::*member) {
    return field_mapper<Class>(member);
  };
}
