#pragma once

#include <fstream>
#include "pixel.hh"

namespace dev
{

template< size_t M, size_t N >
void write_ppm(::std::ofstream& ofs, const image<M,N>& im)
{
  // N is width (number of columns), M is height (number of rows)
  ofs << "P6 " << N << " " << M << " " << color_max << "\n";
  for (size_t i = 0; i < M; ++i)
  {
    ofs.flush();
    for (auto& e : im.row(i))
    {
      ofs << static_cast<char>(e.r)
          << static_cast<char>(e.g)
          << static_cast<char>(e.b);
    }
  }
  ofs.flush();
}

} // namespace dev
