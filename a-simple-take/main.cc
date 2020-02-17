#include <infiniband/verbs.h>

#include "ib.h"

int main() {
  // In the real world this will be an actual ibv_context obtained by calling
  // `ibv_device_open`.
  struct ibv_context *device_context = NULL;

  IbPd pd(device_context);
  // Pass the underlying pointer where required in the future: pd.get()


  return 0;
}
