#ifndef FNP_TRAITS_H_
#define FNP_TRAITS_H_

#include <typeinfo>
#include <algorithm>
#include <string>

// Want to accept any function pointer as value:
// For every type T, accept the type and a value of that type: template<typename T, T f>
// As can see this is not "tight": f can have any type really, but that's good
// enough for a function that will only be used for debugging purposes. And if
// you're concerned, you can make it as "tight" as you need with very little
// work.
template<typename T, T f>
struct FnpTraits {
  static std::string name() {
    std::string pretty_name = __PRETTY_FUNCTION__;

    // type of f will be written in front of it like so:
    // f = ibv_alloc_pd
    std::string start_marker = "f = ", maybe_end_chars= ";,]";
    // Diferent delimiters are there because of clang/gcc, and the possibility
    // that the f might be the last thing written in __PRETTY_FUNCTION__
    // as it will look something like [ T = text text, f = text text ].

    auto start_index = pretty_name.find(start_marker) + start_marker.size();
    auto end_index = pretty_name.find_first_of(maybe_end_chars, start_index);

    return pretty_name.substr(start_index, end_index - start_index);
  }
};

#endif  // FNP_TRAITS_H_
