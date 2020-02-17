#ifndef IB_H_
#define IB_H_
#include <memory>
#include <functional>
#include <type_traits>

#include <infiniband/verbs.h>

#include "fnp_traits.h"
#include "fnp_types.h"
#include "ib_utils.h"

// Ask for the type of the Factory (allocator func), and the factory itself.
// Same goes for the deleter.
// Finally using the packing technique, ask ask for the Args that are
// extracted from the function pointer in the `fnp_types` trait.
template<typename Factory, Factory f, typename Deleter, Deleter d,
  typename = typename fnp_types<decltype(f)>::PackedArgs>
class IbResource;

// The only reason that we need to specilize (as opposed to defining the template
// right away is pattern matching the Args... out of the decltype(f)>::PackedArgs.
template<typename Factory, Factory f, typename Deleter, Deleter d, typename... Args>
class IbResource <Factory, f, Deleter, d, Pack<Args...>> {
 public:
  // Removing the pointer, and then working with the type makes things a bit
  // more readable in the uniquee_ptr and the get function. Again, we'll have to
  // do a bit more work to do the correct thing in the rare cases when the
  // functions that return a struct as opposed to a pointer to a struct.
  using ResourceType = std::remove_pointer_t<typename fnp_types<decltype(f)>::ReturnType>;

  // This is hiding the flexibility of std::unique_ptr from the user of
  // IbResource. Might make more sense to directly ask for the final deleter
  // type when you're creatin a concrete IbResource from the IbResource template.
  std::unique_ptr<ResourceType, void_deleter<ResourceType>> ptr_;

  IbResource(Args... args): ptr_(
      factory_wrapper(f, fnp_traits<Factory, f>::name())(std::forward<Args...>(args)...),
      int_deleter_wrapper(d, fnp_traits<Deleter, d>::name())) { }

  ResourceType *get() const {
    return ptr_.get();
  }
};

// A function like ibv_device_context_by_name is not present in the ibv library.
// The way it works is you obtain a list of devices, iterate over them, and open
// whichever you chose.
// What do we do? We create our own function, do the resource allocation
// manually, and wrap it in an IBResource similar to original ibv_* allocators.
// See ib.cc for the implementation.
struct ibv_context *ibv_device_context_by_name_(const char *name);

using IbvDeviceContextByName = IbResource<
                      decltype(&ibv_device_context_by_name_), &ibv_device_context_by_name_,
                      decltype(&ibv_close_device), &ibv_close_device
                      >;

using IbvAllocPd = IbResource<
                      decltype(&ibv_alloc_pd), &ibv_alloc_pd,
                      decltype(&ibv_dealloc_pd), &ibv_dealloc_pd
                      >;

using IbvRegMr = IbResource<
                      decltype(&ibv_reg_mr), &ibv_reg_mr,
                      decltype(&ibv_dereg_mr), &ibv_dereg_mr
                      >;

#endif  // IB_H_
