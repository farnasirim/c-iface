#include "ib.h"

#include <exception>

IbPd::IbPd(struct ibv_context *ib):
  pd_(nullptr,
      [](struct ibv_pd *pd) {
        if(pd != NULL) { ibv_dealloc_pd(pd); /* ignore return */ } 
        })
{
  struct ibv_pd *maybe_pd = ibv_alloc_pd(ib);
  if(maybe_pd == NULL) {
    // for example
    throw std::exception();
  }
  pd_.reset(maybe_pd);
}

struct ibv_pd *IbPd::get() const {
  return pd_.get();
}
