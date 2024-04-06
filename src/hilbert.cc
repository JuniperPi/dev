#include <typeinfo>

#include "dev.hh"
#include "image.hh"
#include "hilbert.hh"

#define FILENAME    OUTDIR "/hilbert"
#define FILENAME_2  OUTDIR "/hilbert_gapless"

namespace dev
{

template< size_t N >
void hilbert_png(const color_path_t& color_path)
{
  ::std::ofstream ofs(FILENAME "_" + ::std::to_string(N) + ".ppm");
  write_ppm(ofs, scaled_hilbert<N,9-N>(color_path));
  ofs.close();
}

#define CONVERT(N) system("convert " FILENAME "_" #N ".ppm " FILENAME "_" #N ".png")

} // namespace dev

using namespace dev;

int main(int argc, char** argv)
{
  using namespace dev;

  const auto purple =
  color_path_t{pixel{0,96,192}, pixel{96,0,96}, pixel{192,96,0}};

  const auto pinkish =
  color_path_t{pixel{223,127,31}, pixel{223,31,127}, pixel{31,31,223}};

  const auto bright_pinkish =
  color_path_t{pixel{255,128,0}, pixel{255,0,128}, pixel{0,0,255}};


  FLAG(1);
  hilbert_png<1>(purple);
  CONVERT(1);

  FLAG(2);
  hilbert_png<2>(purple);
  CONVERT(2);

  FLAG(3);
  hilbert_png<3>(purple);
  CONVERT(3);

  FLAG(4);
  hilbert_png<4>(purple);
  CONVERT(4);

  FLAG(5);
  hilbert_png<5>(purple);
  CONVERT(5);

  FLAG(6);
  hilbert_png<6>(purple);
  CONVERT(6);

  FLAG(7);
  hilbert_png<7>(purple);
  CONVERT(7);

  FLAG(8);
  hilbert_png<8>(purple);
  CONVERT(8);

  FLAG(9);
  hilbert_png<9>(purple);
  CONVERT(9);

  // gapless
  hilbert_t gapless(1,purple);

  write_png("gapless", gapless.draw<hilbert_dim<10,1>>(10));
/*
  FLAG(gapless);
  ::std::ofstream ofs(FILENAME ".ppm");
  ofs.open(FILENAME_2 ".ppm");
  write_ppm(ofs, gapless.draw<hilbert_dim<10,1>>(10));
  system("convert " FILENAME_2 ".ppm " FILENAME_2 ".png");
  ::std::cout << FILENAME_2 << ".png" << ::std::endl;
  */

  return 0;
}
