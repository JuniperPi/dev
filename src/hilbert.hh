#pragma once

#include <string>
#include <sstream>
#include "image.hh"
#include "integer_math.hh"
#include "color_path.hh"

namespace dev
{

class lindenmayer_t
{
  public:
    lindenmayer_t() : m_str("A") {}

    lindenmayer_t(const size_t n)
    : m_str("A") { iterate(n); }

    void iterate(const size_t n = 1)
    {
      for (size_t i = 0; i < n; ++i)
        produce();
    }

    ::std::string str() const
    {
      ::std::ostringstream os;
      for (const auto& c : m_str)
      {
        if (c != 'A' && c != 'B')
        {
          os << c;
        }
      }
      return os.str();
    }

    size_t size(const size_t step_size) const
    {
      size_t count = 1;
      for (const auto& c : m_str)
      {
        if ('F' == c)
        {
          count += step_size;
        }
      }
      return count;
    }

  private:
    ::std::string m_str;

    void produce()
    {
      ::std::ostringstream os;
      for (const auto& c : m_str)
      {
        switch (c)
        {
          case 'A':
            os << A_str;
            break;
          case 'B':
            os << B_str;
            break;
          default:
            os << c;
        }
      }
      m_str = os.str();
    }

    static constexpr char A_str[12] = "+BF-AFA-FB+";
    static constexpr char B_str[12] = "-AF+BFB+FA-";
};


class hilbert_t
{
  public:
    // constructors
    hilbert_t() : m_step_size(2) {}

    hilbert_t(const size_t s) : m_step_size(s) {}

    hilbert_t(const color_path_t& colors)
    : m_color_path(colors) {}

    hilbert_t(const size_t s, const color_path_t& colors)
    : m_step_size(s), m_color_path(colors) {}

    // getters
    constexpr size_t& step_size() noexcept { return m_step_size; }
    color_path_t& color_path() { return m_color_path; }

    // doer
    template< size_t N >
    image_t<N,N> draw(const size_t redraws) const
    {
      image_t<N,N> im;

      lindenmayer_t lindenmayer(redraws);

      int i = 0, j = 0;
      const size_t curve_len = lindenmayer.size(m_step_size);
      im.at(i,j) = m_color_path.get(0,curve_len);

      const ::std::string lin_str = lindenmayer.str();
      direction_t direction = S;
      size_t count = 0;

      for (const auto& c : lin_str)
      {

        switch (c)
        {
          case 'F':
            for (size_t idx = 0; idx < m_step_size; ++idx)
            {
              move_forward(direction, i, j);

              ++count;

              im.at(i,j) = m_color_path.get(count, curve_len);
            }
            break;

          case '+':
            direction = static_cast<direction_t>((direction + 3) % 4);
            break;

          case '-':
            direction = static_cast<direction_t>((direction + 1) % 4);
            break;
        }
      }
      return im;
    }

  private:
    size_t m_step_size;
    color_path_t m_color_path;

    enum direction_t : int
    { N, E, S, W };

    static constexpr void move_forward(const direction_t d,
                                       int& i, int& j)
    {
      switch (d)
      {
        case N: --i; break;
        case S: ++i; break;
        case E: ++j; break;
        case W: --j; break;
      }
    }
};

template< size_t NumIt, size_t StepSize >
constexpr size_t hilbert_dim;

template< size_t NumIt >
constexpr size_t hilbert_dim<NumIt, 1> = pow2<NumIt>;

template< size_t NumIt >
constexpr size_t hilbert_dim<NumIt, 2> = pow2<NumIt+1>-1;

template< size_t NumIt, size_t ScaleLog >
sq_image_t<hilbert_dim<NumIt,2> * pow2<ScaleLog>>
scaled_hilbert(const color_path_t& color_path)
{
  hilbert_t hilbert(2,color_path);

  auto first_image = hilbert.draw<hilbert_dim<NumIt,2>>(NumIt);

  return scale<pow2<ScaleLog>,
               hilbert_dim<NumIt,2>,
               hilbert_dim<NumIt,2>>(first_image);
}

} // namespace dev
