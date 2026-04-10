#pragma once

#include "./forward.hpp"

namespace ran {

namespace impl {

template<typename T, std::floating_point U, typename Derived>
requires(meta::interpolable<T, U>)
struct EasingMixerBase {
  RAN_DEF T operator()(const T& a, const T& b, U t) const {
    if (t == U{1}) {
      return b;
    }
    return a + static_cast<const Derived&>(*this)(t) * (b - a);
  }
};

} // namespace impl

template<typename T, meta::floating_point U>
struct EasingLinear : public impl::EasingMixerBase<T, U, EasingLinear<T, U>> {
  using impl::EasingMixerBase<T, U, EasingLinear<T, U>>::operator();

  RAN_DEF U operator()(U t) const { return t; }
};

// https://easings.net/
template<typename T, meta::floating_point U>
struct EasingElasticIn : public impl::EasingMixerBase<T, U, EasingElasticIn<T, U>> {
  using impl::EasingMixerBase<T, U, EasingElasticIn<T, U>>::operator();

  RAN_DEF U operator()(U t) const {
    const U c4 = U{2} * U{M_PI} / U{3};
    if (t <= U{0} || t >= U{1}) {
      return t;
    }
    return -std::pow(U{2}, U{10} * t - U{10}) * std::sin((t * U{10} - (U{10.75f})) * c4);
  }
};

template<typename T, meta::floating_point U>
struct EasingBackInOut : public impl::EasingMixerBase<T, U, EasingBackInOut<T, U>> {
  using impl::EasingMixerBase<T, U, EasingBackInOut<T, U>>::operator();

  RAN_DEF U operator()(U t) const {
    const U c2 = U{1.70158f * 1.525f};
    if (t < U{.5f}) {
      return (std::pow(U{2} * t, U{2}) * ((c2 + U{1}) * U{2} * t - c2)) / U{2};
    }
    return (std::pow(U{2} * t - U{2}, U{2}) * ((c2 + U{1}) * (t * U{2} - U{2}) + c2) + U{2}) /
           U{2};
  }
};

template<typename T, meta::floating_point U>
struct EasingPow : public impl::EasingMixerBase<T, U, EasingPow<T, U>> {
  using impl::EasingMixerBase<T, U, EasingPow<T, U>>::operator();

  RAN_DEF EasingPow(u32 p) : _p{p} {}

  RAN_DEF U operator()(U t) const {
    U res{1};
    for (u32 i = _p; i--;) {
      res *= t;
    }
    return res;
  }

private:
  u32 _p;
};

namespace impl {

template<typename T, std::floating_point U, meta::lerp_fn<T, U> F, typename Derived>
class LerperBase : private F {
public:
  using interpolator_type = F;

public:
  RAN_DEF LerperBase(const T& first, const T& last) : F{}, _first{first}, _last{last} {}

  RAN_DEF LerperBase(const T& first, const T& last, const F& lerper) :
      F{lerper}, _first{first}, _last{last} {}

  RAN_DEF LerperBase(const T& first, const T& last, F&& lerper) :
      F{std::move(lerper)}, _first{first}, _last{last} {}

  template<typename... Args>
  RAN_DEF LerperBase(const T& first, const T& last, std::in_place_t, Args&&... args) :
      F{std::forward<Args>(args)...}, _first{first}, _last{last} {}

protected:
  RAN_DEF T evaluate(U t) const { return get_interpolator()(_first, _last, t); }

public:
  RAN_DEF T first() const { return _first; }

  RAN_DEF T last() const { return _last; }

  RAN_DEF Derived& first(const T& val) {
    _first = val;
    return static_cast<Derived&>(*this);
  }

  RAN_DEF Derived& last(const T& val) {
    _last = val;
    return static_cast<Derived&>(*this);
  }

  RAN_DEF F& get_interpolator() { return static_cast<F&>(*this); }

  RAN_DEF const F& get_interpolator() const { return static_cast<const F&>(*this); }

private:
  T _first, _last;
};

} // namespace impl

template<typename T, meta::floating_point U, meta::lerp_fn<T, U> Fn>
class DeltaLerpFn : public impl::LerperBase<T, U, Fn, DeltaLerpFn<T, U, Fn>> {
private:
  static_assert(meta::interpolable<T, U>, "T needs to be an interpolable type");
  using base_t = impl::LerperBase<T, U, Fn, DeltaLerpFn<T, U, Fn>>;

public:
  using base_t::base_t;

public:
  RAN_DEF T eval(U t) const { return base_t::evaluate(t); }

  RAN_DEF T eval(U t, U alpha) const { return eval(t + alpha); }

public:
  RAN_DEF T operator()(U t) const { return eval(t); }

  RAN_DEF T operator()(U t, U alpha) const { return eval(t, alpha); }
};

template<typename T, meta::floating_point U, meta::lerp_fn<T, U> Fn, u32 StepSize>
class StepLerpFn : public impl::LerperBase<T, U, Fn, StepLerpFn<T, U, Fn, StepSize>> {
private:
  static_assert(meta::interpolable<T, U>, "T needs to be an interpolable type");
  using base_t = impl::LerperBase<T, U, Fn, StepLerpFn<T, U, Fn, StepSize>>;

public:
  static RAN_CONSTEXPR u32 step_size = StepSize;

public:
  using base_t::base_t;

private:
  RAN_DEF T _eval(U delta) const { return base_t::evaluate(delta / static_cast<U>(steps())); }

public:
  RAN_DEF T eval(s32 steps) const { return _eval(static_cast<U>(steps)); }

  RAN_DEF T eval(s32 steps, U alpha) const { return _eval(static_cast<U>(steps) + alpha); }

public:
  RAN_DEF T operator()(s32 steps) const { return eval(steps); }

  RAN_DEF T operator()(s32 steps, U alpha) const { return eval(steps, alpha); }

public:
  RAN_DEF u32 steps() const { return step_size; }
};

template<typename T, typename U, typename Fn>
class StepLerpFn<T, U, Fn, dynamic_step> :
    public impl::LerperBase<T, U, Fn, StepLerpFn<T, U, Fn, dynamic_step>> {
private:
  static_assert(meta::interpolable<T, U>, "T needs to be an interpolable type");
  using base_t = impl::LerperBase<T, U, Fn, StepLerpFn<T, U, Fn, dynamic_step>>;

public:
  static RAN_CONSTEXPR u32 step_size = dynamic_step;

public:
  RAN_DEF StepLerpFn(const T& first, const T& last, u32 steps) :
      base_t{first, last}, _steps{steps} {}

  RAN_DEF StepLerpFn(const T& first, const T& last, u32 steps, const Fn& lerper) :
      base_t{first, last, lerper}, _steps{steps} {}

  RAN_DEF StepLerpFn(const T& first, const T& last, u32 steps, Fn&& lerper) :
      base_t{first, last, std::move(lerper)}, _steps{steps} {}

  template<typename... Args>
  explicit RAN_DEF StepLerpFn(const T& first, const T& last, u32 steps, std::in_place_t t,
                              Args&&... args) :
      base_t{first, last, t, std::forward<Args>(args)...}, _steps{steps} {}

private:
  RAN_DEF T _eval(U delta) const { return base_t::evaluate(delta / static_cast<U>(steps())); }

public:
  RAN_DEF T eval(s32 steps) const { return _eval(static_cast<U>(steps)); }

  RAN_DEF T eval(s32 steps, U alpha) const { return _eval(static_cast<U>(steps) + alpha); }

public:
  RAN_DEF T operator()(s32 steps) const { return eval(steps); }

  RAN_DEF T operator()(s32 steps, U alpha) const { return eval(steps, alpha); }

public:
  RAN_DEF u32 steps() const { return _steps; }

  RAN_DEF StepLerpFn& steps(u32 value) {
    _steps = value;
    return *this;
  }

private:
  u32 _steps;
};

template<typename T, meta::floating_point U, meta::lerp_fn<T, U> Fn>
class DeltaLerp : public impl::LerperBase<T, U, Fn, DeltaLerp<T, U, Fn>> {
private:
  static_assert(meta::interpolable<T, U>, "T needs to be an interpolable type");
  using base_t = impl::LerperBase<T, U, Fn, DeltaLerp<T, U, Fn>>;

public:
  using base_t::base_t;

  explicit RAN_DEF DeltaLerp(const T& first, const T& last, U age) :
      base_t{first, last}, _t{age} {}

  RAN_DEF DeltaLerp(const T& first, const T& last, U age, const Fn& lerper) :
      base_t{first, last, lerper}, _t{age} {}

  RAN_DEF DeltaLerp(const T& first, const T& last, U age, Fn&& lerper) :
      base_t{first, last, std::move(lerper)}, _t{age} {}

  template<typename... Args>
  explicit RAN_DEF DeltaLerp(const T& first, const T& last, U age, std::in_place_t tag,
                             Args&&... args) :
      base_t{first, last, tag, std::forward<Args>(args)...}, _t{age} {}

public:
  RAN_DEF T value() const { return base_t::evaluate(_t); }

  RAN_DEF T value(U alpha) const { return base_t::evaluate(_t + alpha); }

public:
  RAN_DEF T operator*() const { return value(); }

public:
  RAN_DEF U age() const { return _t; }

  RAN_DEF DeltaLerp& tick(U delta) {
    _t += delta;
    return *this;
  }

  RAN_DEF DeltaLerp& age(U val) {
    _t = val;
    return *this;
  }

private:
  U _t{};
};

template<typename T, meta::floating_point U, meta::lerp_fn<T, U> Fn, u32 StepSize>
class StepLerp : public impl::LerperBase<T, U, Fn, StepLerp<T, U, Fn, StepSize>> {
private:
  static_assert(meta::interpolable<T, U>, "T needs to be an interpolable type");
  using base_t = impl::LerperBase<T, U, Fn, StepLerp<T, U, Fn, StepSize>>;

public:
  static RAN_CONSTEXPR u32 step_size = StepSize;

public:
  using base_t::base_t;

  explicit RAN_DEF StepLerp(const T& first, const T& last, s32 age) :
      base_t{first, last}, _age{age} {}

  RAN_DEF StepLerp(const T& first, const T& last, s32 age, const Fn& lerper) :
      base_t{first, last, lerper}, _age{age} {}

  RAN_DEF StepLerp(const T& first, const T& last, s32 age, Fn&& lerper) :
      base_t{first, last, std::move(lerper)}, _age{age} {}

  template<typename... Args>
  explicit RAN_DEF StepLerp(const T& first, const T& last, s32 age, std::in_place_t t,
                            Args&&... args) :
      base_t{first, last, t, std::forward<Args>(args)...}, _age{age} {}

private:
  RAN_DEF T _eval(U delta) const { return base_t::evaluate(delta / static_cast<U>(steps())); }

public:
  RAN_DEF T value() const { return _eval(static_cast<U>(_age)); }

  RAN_DEF T value(U alpha) const { return _eval(static_cast<U>(_age) + alpha); }

public:
  RAN_DEF T operator*() const { return value(); }

public:
  RAN_DEF u32 steps() const { return step_size; }

  RAN_DEF s32 age() const { return _age; }

  RAN_DEF StepLerp& tick(s32 count = 1) {
    _age += count;
    return *this;
  }

  RAN_DEF StepLerp& tick_loop(s32 count = 1) {
    _age = (_age + count) % static_cast<s32>(steps());
    return *this;
  }

  RAN_DEF StepLerp& age(s32 value) {
    _age = value;
    return *this;
  }

private:
  s32 _age{};
};

template<typename T, typename U, typename Fn>
class StepLerp<T, U, Fn, dynamic_step> :
    public impl::LerperBase<T, U, Fn, StepLerp<T, U, Fn, dynamic_step>> {
private:
  static_assert(meta::interpolable<T, U>, "T needs to be an interpolable type");
  using base_t = impl::LerperBase<T, U, Fn, StepLerp<T, U, Fn, dynamic_step>>;

public:
  static RAN_CONSTEXPR u32 step_size = dynamic_step;

public:
  RAN_DEF StepLerp(const T& first, const T& last, u32 steps) :
      base_t{first, last}, _steps{steps}, _age{} {}

  RAN_DEF StepLerp(const T& first, const T& last, u32 steps, const Fn& lerper) :
      base_t{first, last, lerper}, _steps{steps}, _age{} {}

  RAN_DEF StepLerp(const T& first, const T& last, u32 steps, Fn&& lerper) :
      base_t{first, last, std::move(lerper)}, _steps{steps}, _age{} {}

  template<typename... Args>
  explicit RAN_DEF StepLerp(const T& first, const T& last, u32 steps, std::in_place_t tag,
                            Args&&... args) :
      base_t{first, last, tag, std::forward<Args>(args)...}, _steps{steps}, _age{} {}

  explicit RAN_DEF StepLerp(const T& first, const T& last, u32 steps, s32 age) :
      base_t{first, last}, _steps{steps}, _age{age} {}

  RAN_DEF StepLerp(const T& first, const T& last, u32 steps, s32 age, const Fn& lerper) :
      base_t{first, last, lerper}, _steps{steps}, _age{age} {}

  RAN_DEF StepLerp(const T& first, const T& last, u32 steps, s32 age, Fn&& lerper) :
      base_t{first, last, std::move(lerper)}, _steps{steps}, _age{age} {}

  template<typename... Args>
  explicit RAN_DEF StepLerp(const T& first, const T& last, u32 steps, s32 age, std::in_place_t tag,
                            Args&&... args) :
      base_t{first, last, tag, std::forward<Args>(args)...}, _steps{steps}, _age{age} {}

private:
  RAN_DEF T _eval(U delta) const { return base_t::evaluate(delta / static_cast<U>(steps())); }

public:
  RAN_DEF T value() const { return _eval(static_cast<U>(_age)); }

  RAN_DEF T value(U alpha) const { return _eval(static_cast<U>(_age) + alpha); }

public:
  RAN_DEF T operator*() const { return value(); }

public:
  RAN_DEF u32 steps() const { return _steps; }

  RAN_DEF StepLerp& steps(u32 value) {
    _steps = value;
    return *this;
  }

  RAN_DEF s32 age() const { return _age; }

  RAN_DEF StepLerp& tick(s32 count = 1) {
    _age += count;
    return *this;
  }

  RAN_DEF StepLerp& tick_loop(s32 count = 1) {
    _age = (_age + count) % static_cast<s32>(steps());
    return *this;
  }

  RAN_DEF StepLerp& age(s32 value) {
    _age = value;
    return *this;
  }

private:
  u32 _steps;
  s32 _age;
};

} // namespace ran
