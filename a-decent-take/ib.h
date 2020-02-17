#ifndef IB_H_
#define IB_H_

#include <functional>
#include <memory>

#include <infiniband/verbs.h>

class IbPd {
 public:
  IbPd(struct ibv_context *);
  struct ibv_pd *get() const;

 private:
  std::unique_ptr<struct ibv_pd, std::function<void(struct ibv_pd*)>> pd_;
};

#endif  // IB_H_

