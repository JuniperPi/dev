#pragma once

#include <fstream>
#include <array>
#include <memory>


namespace dev
{

constexpr int16_t color_max = 255;

struct pixel
{
  int16_t r;
  int16_t g;
  int16_t b;

  constexpr int16_t& operator[] (const size_t n) noexcept
  { return n == 0 ? r : (n == 1 ? g : b); }

  constexpr const int16_t& operator[] (const size_t n) const noexcept
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

template< size_t M, size_t N >
class image
{
  public:
    using value_type = pixel;
    using row_type = ::std::array<pixel, N>;
    using row_pointer = ::std::unique_ptr<row_type>;
    using container = ::std::array<row_pointer, M>;

    constexpr image()
    {
      for (auto& row : m_cont)
      {
        row = ::std::make_unique<row_type>(row_type{black});
      }
    }

    // element access

    constexpr pixel& at(const size_t i, const size_t j) noexcept
    { return m_cont.at(i)->at(j); }

    constexpr const pixel& at(const size_t i, const size_t j) const noexcept
    { return m_cont.at(i)->at(j); }

    // row access

    constexpr row_type& row(const size_t i) noexcept
    { return *(m_cont.at(i)); }

    constexpr const row_type& row(const size_t i) const noexcept
    { return *(m_cont.at(i)); }

    // Modify

    constexpr void fill(const pixel& pix)
    {
      for (auto& row : m_cont)
      {
        row->fill(pix);
      }
    }

  private:
    container m_cont;
};

} // namespace dev
