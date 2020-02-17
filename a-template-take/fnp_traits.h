#ifndef IB_TRAITS_H_
#define IB_TRAITS_H_

#include <typeinfo>
#include <algorithm>
#include <string>

template<typename T, T f>
struct fnp_traits {
  static std::string name() {
    std::string pretty_name = __PRETTY_FUNCTION__;
    std::string start_marker = "f = ", maybe_end_chars= ";,]";
    auto start_index = pretty_name.find(start_marker) + start_marker.size();
    auto end_index = pretty_name.find_first_of(maybe_end_chars, start_index);

    return pretty_name.substr(start_index, end_index - start_index);
  }
};

#endif
