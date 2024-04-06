#include "dev.hh"
#include "image.hh"
#include "serpenski.hh"

int main(int argc, char** argv)
{
  using namespace dev;
  auto im = serpenski<1080,1920>();
  write_png("serpenski", im);
  fill_down(im);
  write_png("serpenski_filled", im);

  return 0;
}
