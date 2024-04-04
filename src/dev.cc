#include <typeinfo>

#include "dev.hh"
#include "ppm.hh"
#include "draw_hilbert.hh"

#define FILENAME  "hilbert"
#define FILENAME_2  "hilbert_gapless"

#define FILEPATH  OUTDIR "/" FILENAME
#define FILEPATH_2  OUTDIR "/" FILENAME_2

using namespace dev;

int main(int argc, char** argv)
{
  using namespace dev;

  FLAG(construct);
  hilbert_t hilbert(2,
  {pixel{223,127,31},pixel{223,31,127},pixel{31,31,223}});
  //{pixel{255,128,0},pixel{255,0,128},pixel{0,0,255}});

  constexpr size_t I = 9;
  constexpr size_t M = pow2<I+1>-1;

  constexpr size_t J = 10;
  constexpr size_t N = pow2<J>;

  FLAG(draw hilbert);
  ::std::ofstream ofs(FILEPATH ".ppm");
  write_ppm(ofs, hilbert.draw<M>(I));
  ofs.close();
  system("convert " FILEPATH ".ppm " FILEPATH ".png");

  hilbert.step_size() = 1;

  FLAG(draw hilbert_gapless);
  ofs.open(FILEPATH_2 ".ppm");
  write_ppm(ofs, hilbert.draw<N>(J));
  system("convert " FILEPATH_2 ".ppm " FILEPATH_2 ".png");

  return 0;
}
