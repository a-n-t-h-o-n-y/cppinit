#ifndef UTILITY_PROPERTY_HPP
#define UTILITY_PROPERTY_HPP
#include <signals/signals.hpp>

#include <cstdint>
#include <iostream>
#include <utility>

namespace utility {

/// Wraps a value and provides get/set members. Setting the value emits a
/// Signal which passes on the value set.
template <typename T>
class Property {
   public:
    /// Default construct object of type T.
    Property(){};

    /// Construct object of type T that is constructible from type U.
    template <typename... Args>
    Property(Args&&... args) : value_{std::forward<Args>(args)...}
    {}

    /// Return a non-const reference to the property's value.
    auto get() -> T& { return value_; }

    /// Return a const reference to the property's value.
    auto get() const -> T const& { return value_; }

    /// Set value from any U object that can be constructed into a T object.
    template <typename U>
    void set(U&& value)
    {
        if (value != value_) {
            value_ = std::forward<U>(value);
            on_change_(value_);
        }
    }

    /// Return a reference to the signal emitted on change of value.
    auto on_change() -> sig::Signal<void(T const&)>& { return on_change_; }

    /// Return a const reference to the signal emitted on change of value.
    auto on_change() const -> sig::Signal<void(T const&)> const&
    {
        return on_change_;
    }

   private:
    T value_;
    sig::Signal<void(T const&)> on_change_;
};

/// std::ostream operator
template <typename T>
auto operator<<(std::ostream& os, Property<T> const& prop) -> std::ostream&
{
    return os << prop.get();
}

/// std::istream operator
template <typename T>
auto operator>>(std::istream& is, Property<T>& prop) -> std::istream&
{
    auto temp = T();
    is >> temp;
    prop.set(std::move(temp));
    return is;
}

// Specialized default constructors. UB if pod type comparison with
// uninitialized value in set member function.
template <>
Property<std::int8_t>::Property() : value_{0}
{}

template <>
Property<std::int16_t>::Property() : value_{0}
{}

template <>
Property<std::int32_t>::Property() : value_{0}
{}

template <>
Property<std::int64_t>::Property() : value_{0}
{}

template <>
Property<std::uint8_t>::Property() : value_{0}
{}

template <>
Property<std::uint16_t>::Property() : value_{0}
{}

template <>
Property<std::uint32_t>::Property() : value_{0}
{}

template <>
Property<std::uint64_t>::Property() : value_{0}
{}

template <>
Property<float>::Property() : value_{0.f}
{}

template <>
Property<double>::Property() : value_{0.}
{}

template <>
Property<bool>::Property() : value_{false}
{}

template <>
Property<char>::Property() : value_{static_cast<char>(0)}
{}

template <>
Property<char16_t>::Property() : value_{static_cast<char16_t>(0)}
{}

template <>
Property<char32_t>::Property() : value_{static_cast<char32_t>(0)}
{}

}  // namespace utility
#endif  // UTILITY_PROPERTY_HPP
