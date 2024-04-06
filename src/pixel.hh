#pragma once

#include <fstream>
#include <array>
#include <memory>


namespace dev
{

constexpr int color_max = 255;

struct pixel
{
  int r;
  int g;
  int b;

  constexpr int& operator[] (const size_t n) noexcept
  { return n == 0 ? r : (n == 1 ? g : b); }

  constexpr const int& operator[] (const size_t n) const noexcept
  { return n == 0 ? r : (n == 1 ? g : b); }

};

::std::ostream& operator<<(::std::ostream& os, const pixel& pix)
{ return os << "[" << pix.r << " " << pix.g << " " << pix.b << "]"; }

constexpr pixel black = pixel{0,0,0};
constexpr pixel white = pixel{color_max,color_max,color_max};

constexpr pixel red   = pixel{color_max,0,0};
constexpr pixel green = pixel{0,color_max,0};
constexpr pixel blue  = pixel{0,0,color_max};

// not sure about these
constexpr pixel yellow = pixel{color_max,color_max,0};
constexpr pixel magenta = pixel{color_max,0,color_max};
constexpr pixel cyan = pixel{0,color_max,color_max};

// logical operators
constexpr bool operator == (const pixel p, const pixel q)
{ return p.r == q.r && p.g == q.g && p.b == q.b; }

constexpr bool operator != (const pixel p, const pixel q)
{ return p.r != q.r || p.g != q.g || p.b != q.b; }


} // namespace dev
