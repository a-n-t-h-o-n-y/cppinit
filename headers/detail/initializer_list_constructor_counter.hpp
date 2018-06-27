#ifndef UTILITY_DETAIL_INITIALIZER_LIST_CONSTRUCTOR_COUNTER_HPP
#define UTILITY_DETAIL_INITIALIZER_LIST_CONSTRUCTOR_COUNTER_HPP
#include <string>

#include "../count_t.hpp"
#include "../type_info.hpp"

namespace utility {
namespace detail {

template <typename T>
class Initializer_list_constructor_counter {
   public:
    /// Increment the counter by one. Should be called by the class inheriting
    /// this class in the initializer list constructor.
    static void increment_initializer_list_constructor_count();

    /// Retrieve number of times the initializer list constructor has been
    /// called.
    static Count_t get_initializer_list_constructor_count();

    /// Set count of initializer list constructor to zero.
    static void reset_initializer_list_constructor_count();

    /// Generate string with count info for the initializer list constructor.
    static std::string initializer_list_constructor_count_as_string();

   private:
    static Count_t initializer_list_constructor_count_;
};

// IMPLEMENTATION - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
template <typename T>
Count_t Initializer_list_constructor_counter<
    T>::initializer_list_constructor_count_{0};

template <typename T>
void Initializer_list_constructor_counter<
    T>::increment_initializer_list_constructor_count() {
    ++initializer_list_constructor_count_;
}

template <typename T>
Count_t Initializer_list_constructor_counter<
    T>::get_initializer_list_constructor_count() {
    return initializer_list_constructor_count_;
}

template <typename T>
void Initializer_list_constructor_counter<
    T>::reset_initializer_list_constructor_count() {
    initializer_list_constructor_count_ = 0;
}

template <typename T>
std::string Initializer_list_constructor_counter<
    T>::initializer_list_constructor_count_as_string() {
    std::string description{utility::get_type_info<T>()};
    description.append("(std::initializer_list<");
    description.append(utility::get_type_info<std::remove_extent<T>::type>());
    description.append(">) called ");
    description.append(std::to_string(initializer_list_constructor_count_));
    description.append(" times.");
    return description;
}

}  // namespace detail
}  // namespace utility
#endif  // UTILITY_DETAIL_INITIALIZER_LIST_CONSTRUCTOR_COUNTER_HPP
