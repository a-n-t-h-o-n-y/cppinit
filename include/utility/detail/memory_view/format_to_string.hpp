#ifndef UTILITY_DETAIL_MEMORY_VIEW_FORMAT_TO_STRING_HPP
#define UTILITY_DETAIL_MEMORY_VIEW_FORMAT_TO_STRING_HPP
#include <bitset>
#include <cstddef>
#include <ios>
#include <sstream>
#include <string>

#include "to_upper_case.hpp"

namespace utility::detail::memory_view {

template <std::size_t N>
auto format_to_string(const std::bitset<N>& bits, std::ios_base::fmtflags base)
    -> std::string
{
    auto const bit_limit = sizeof(unsigned long long) * 8;
    if (bits.size() > bit_limit)
        return "";
    auto ss = std::stringstream{};
    ss.setf(base, std::ios_base::basefield);
    ss << bits.to_ullong();
    return to_upper_case_copy(ss.str());
}

}  // namespace utility::detail::memory_view
#endif  // UTILITY_DETAIL_MEMORY_VIEW_FORMAT_TO_STRING_HPP
