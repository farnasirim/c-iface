#include <infiniband/verbs.h>

#include "ib.h"

int main() {
  IbvDeviceContextByName device_context("mlnx_0");  
  IbvAllocPd pd(device_context.get());  

  return 0;
}
