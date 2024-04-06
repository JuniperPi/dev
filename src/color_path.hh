#pragma once

#include <initializer_list>
#include <vector>
#include "pixel.hh"

namespace dev
{

struct color_path_t
{
  ::std::vector<pixel> values;

  color_path_t() {}
  color_path_t(::std::initializer_list<pixel> il)
  : values(il) {}


  pixel get(const size_t pos, const size_t max) const
  {
    if (values.size() == 0)
    {
      return white;
    }
    if (values.size() == 1)
    {
      return values.front();
    }

    double val_idx = static_cast<double>(pos) * (values.size()-1) / max;
    const double coef = modf(val_idx, &val_idx);

    auto lambda = [&](const size_t i)->int16_t
    {
      return static_cast<int16_t>((1 - coef) * values.at(val_idx)[i]
          + coef * values.at(val_idx+1)[i]);
    };

    return pixel{ lambda(0), lambda(1), lambda(2) };
  }
};

} // namespace dev
