#ifndef IB_UTILS_H_
#define IB_UTILS_H_

#include <functional>
#include <memory>
#include <iostream>

template<typename T>
using void_deleter = std::function<void(T*)>;

template<typename T>
void_deleter<T> int_deleter_wrapper(int (*orig_deleter)(T*), std::string msg)
{
  return [orig_deleter, msg_capture = std::move(msg)](T *obj) -> void {
    if(orig_deleter(obj)) {
      perror(msg_capture.c_str());
    }
  };
}

template<typename Res, typename ...Args>
using resource_factory = std::function<Res*(Args...)>;

template<typename Res, typename ...Args>
resource_factory<Res, Args...> factory_wrapper(Res *(*orig_factory)(Args...), std::string msg) {
  return [orig_factory, msg_capture = std::move(msg)](Args&&... args) -> Res* {
    Res *ret = orig_factory(std::forward<Args...>(args...));
    if(ret == NULL) {
      perror(msg_capture.c_str());
      std::abort();
    }
    return ret;
  };
}

#endif
