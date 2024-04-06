#pragma once

#include <array>
#include <vector>

namespace dev
{

template< size_t M, size_t N >
image_t<M,N> serpenski()
{
  image_t<M,N> im;
  im.fill(black);
  im.at(0,N/2) = green;

  // due to sparsity, just maintain a list of filled indices
  ::std::array<::std::vector<size_t>,M> valid_idx =
    { ::std::vector<size_t>{N/2} };

  for (size_t i = 0; i < M-1; ++i)
  {
    const auto& top_row = valid_idx.at(i);
    auto& bottom_row = valid_idx.at(i+1);

    auto left_pix = [&](const size_t j) -> pixel
    {
      const pixel pix = im.at(i,j+1);
      return pixel{ ::std::max(0,   pix.r-1),
                    ::std::max(0,   pix.g - (0 == (i % 3) ? 1 : 0)),
                    ::std::min(255, pix.b+1) };
    };

    auto right_pix = [&](const size_t j) -> pixel
    {
      const pixel pix = im.at(i,j-1);
      return pixel{ ::std::min(255, pix.r+1),
                    ::std::max(0,   pix.g - (0 == (i % 3) ? 1 : 0)),
                    ::std::max(0,   pix.b-1) };
    };

    auto light_up = [&](const size_t j, const pixel pix)
    {
      bottom_row.push_back(j);
      im.at(i+1, j) = pix;
    };

    // first pixel
    if (top_row.front() > 0)
    {
      const size_t j = top_row.front() - 1;
      light_up(j, left_pix(j));
    }

    // middle pixels
    for (auto prev = top_row.cbegin(), next = ::std::next(prev);
         next != top_row.cend(); ++prev, ++next)
    {
      if (*prev != *next - 2)
      {
        light_up(*prev + 1, right_pix(*prev + 1));
        light_up(*next - 1, left_pix(*next - 1));
      }
    }

    // last pixel
    if (top_row.back() != N-1)
    {
      const size_t j = top_row.back() + 1;
      light_up(j, right_pix(j));
    }
  }

  return im;
}

} // namespace dev
