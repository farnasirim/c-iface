#include "fnp_types.h"

#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

#include <functional>

template<typename FunctionPointer, typename = typename fnp_types<FunctionPointer>::PackedArgs>
class Example;

using SpecType = int (*)(int);

template<typename... Args>
class Example<SpecType, Pack<Args...>> {
 public:
  Example(SpecType fptr): fptr_(fptr) { }
  int forwarder(Args&&... args) {
    return close(std::forward<Args...>(args)...);
  }
 private:
  SpecType fptr_;
};


int main() {
  Example<SpecType> e(close);
  e.forwarder(open("/dev/stdin", O_RDONLY));  // close(open(...));
  
  return 0;
}
