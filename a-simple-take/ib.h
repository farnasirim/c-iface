#ifndef IB_H_
#define IB_H_

#include <infiniband/verbs.h>

class IbPd {
 public:
  IbPd(struct ibv_context *);
  struct ibv_pd *get() const;
  ~IbPd();

  IbPd(const IbPd&) = delete;

 private:
  struct ibv_pd *pd_;
};

#endif  // IB_H_

