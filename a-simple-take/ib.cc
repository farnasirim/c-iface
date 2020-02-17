#include "ib.h"

#include <exception>

IbPd::IbPd(struct ibv_context *ib) {
  struct ibv_pd *maybe_pd = ibv_alloc_pd(ib);
  if(maybe_pd == NULL) {
    // for example
    throw std::exception();
  }
  pd_ = maybe_pd;
}

struct ibv_pd *IbPd::get() const {
  return pd_;
}

IbPd::~IbPd() {
  if(pd_ != NULL) {
    int status = ibv_dealloc_pd(pd_);
    if(status) {
      // Oops, cannot throw out of the dtor. Not much we can do anyway.
    }
  }
}
