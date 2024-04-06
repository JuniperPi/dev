#pragma once

namespace dev
{

template< size_t N >
constexpr size_t pow2 = 2 * pow2<N-1>;

template<>
constexpr size_t pow2<0> = 1;

} // namespace dev

