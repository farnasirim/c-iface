#ifndef FNP_TYPES_H_
#define  FNP_TYPES_H_

template<typename... Args>
struct Pack { };

template<typename FactoryType>
struct FnpTypes;

template <typename Res, typename... Args>
struct FnpTypes<Res (*)(Args...)> {
 public:
  using ReturnType = Res;
  using PackedArgs = Pack<Args...>;
};

#endif  // FNP_TYPES_H_
