#pragma once

#include <vector>
#include <string>
#include <sstream>

namespace dev
{

template< size_t N >
constexpr size_t pow2 = 2 * pow2<N-1>;

template<>
constexpr size_t pow2<0> = 1;

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

class hilbert_t
{
  public:
    // constructors
    hilbert_t() : m_step_size(2) {}

    hilbert_t(const size_t s) : m_step_size(s) {}

    hilbert_t(::std::initializer_list<pixel> il)
    : m_color_path(il) {}

    hilbert_t(const size_t s, ::std::initializer_list<pixel> il)
    : m_step_size(s), m_color_path(il) {}

    // getters
    constexpr size_t& step_size() noexcept { return m_step_size; }
    color_path_t& color_path() { return m_color_path; }

    // doer
    template< size_t N >
    image<N,N> draw(const size_t redraws) const
    {
      image<N,N> im;

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

} // namespace dev
