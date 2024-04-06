#pragma once

#include <fstream>
#include "pixel.hh"

namespace dev
{

template< size_t M, size_t N >
class image_t
{
  public:
    using value_type = pixel;
    using row_type = ::std::array<pixel, N>;
    using row_pointer = ::std::unique_ptr<row_type>;
    using container = ::std::array<row_pointer, M>;

    constexpr image_t()
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

template< size_t N >
using sq_image_t = image_t<N,N>;

/* Manipulate images */

template< size_t Scale, size_t M, size_t N >
image_t<Scale*M, Scale*N> scale(const image_t<M,N>& im)
{
  image_t<Scale*M, Scale*N> out;

  for (size_t i = 0; i < M; ++i)
  {
    for (size_t j = 0; j < N; ++j)
    {
      const pixel& pix = im.at(i,j);

      for (size_t si = 0; si < Scale; ++si)
      {
        for (size_t sj = 0; sj < Scale; ++sj)
        {
          out.at(Scale*i + si, Scale*j +sj) = pix;
        }
      }
    }
  }

  return out;
}

template< size_t M, size_t N >
image_t<M,N>& fill_down(image_t<M,N>& im)
{
  for (size_t i = 0; i < M-1; ++i)
  {
    for (size_t j = 0; j < N; ++j)
    {
      if (black == im.at(i+1, j))
      {
        im.at(i+1, j) = im.at(i,j);
      }
    }
  }
  return im;
}

template< size_t M, size_t N >
image_t<M,N>& replace(image_t<M,N>& im, const pixel p, const pixel q)
{
  for (size_t i = 0; i < M; ++i)
  {
    for (auto& pix : im.row(i))
    {
      if (p == pix)
      {
        pix = q;
      }
    }
  }
  return im;
}


/* Write images to files */

template< size_t M, size_t N >
void write_ppm(::std::ofstream& ofs, const image_t<M,N>& im)
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

template< size_t M, size_t N >
void write_png(const ::std::string& filename, const image_t<M,N>& im)
{
  ::std::ofstream ofs(OUTDIR "/" + filename + ".ppm");
  write_ppm(ofs, im);
  auto call_convert = "convert "
                 OUTDIR "/" + filename + ".ppm "
                 OUTDIR "/" + filename + ".png";
  system(call_convert.c_str());

  auto call_rm = "rm " OUTDIR "/" + filename + ".ppm";
  system(call_rm.c_str());
}


} // namespace dev
