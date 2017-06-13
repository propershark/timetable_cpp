#pragma once

#include "gtfs/types.h"
#include <experimental/optional>

namespace gtfs {
  template<class Class>
  struct field_mapper {
    template<class U>
    using optional = std::experimental::optional<U>;

    bool        Class::*bool_target;
    std::string Class::*string_target;
    int         Class::*int_target;
    double      Class::*double_target;
    Type        type;

    optional<bool>        default_bool;
    optional<std::string> default_string;
    optional<int>         default_int;
    optional<double>      default_double;

    explicit field_mapper() = default;
    explicit field_mapper(bool        Class::*member) : bool_target(member),    type(tBOOL)   {};
    explicit field_mapper(std::string Class::*member) : string_target(member),  type(tSTRING) {};
    explicit field_mapper(int         Class::*member) : int_target(member),     type(tINT)    {};
    explicit field_mapper(double      Class::*member) : double_target(member),  type(tDOUBLE) {};

    explicit field_mapper(bool        Class::*member, bool        default_val) : bool_target(member),   type(tBOOL),   default_bool(default_val)   {};
    explicit field_mapper(std::string Class::*member, std::string default_val) : string_target(member), type(tSTRING), default_string(default_val) {};
    explicit field_mapper(int         Class::*member, int         default_val) : int_target(member),    type(tINT),    default_int(default_val)    {};
    explicit field_mapper(double      Class::*member, double      default_val) : double_target(member), type(tDOUBLE), default_double(default_val) {};

    inline void apply(Class& inst, optional<int> val) const    { inst.*int_target = val.value_or(*default_int); }
    inline void apply(Class& inst, optional<bool> val) const   { inst.*bool_target = val.value_or(*default_bool); }
    inline void apply(Class& inst, optional<double> val) const { inst.*double_target = val.value_or(*default_double); }

    // For backwards compatibility, applying a string will always fall back to
    // an empty string if no default is available.
    inline void apply(Class& inst, optional<std::string> val) const { 
      inst.*string_target = val.value_or(default_string.value_or("")); 
    }
  };

  template<class Class, typename ValueType>
  constexpr auto make_field_mapper(ValueType Class::*member) {
    return field_mapper<Class>(member);
  };

  template<class Class, typename ValueType>
  constexpr auto make_field_mapper(ValueType Class::*member, ValueType default_val) {
    return field_mapper<Class>(member, default_val);
  };
}
