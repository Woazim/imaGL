#pragma once
#include "loader.h"
#include "public/imaGL/imaGL.h"

#ifdef _HAS_PNG
#include <png.h>

namespace imaGL {

  class CLoaderPNG :
    public ILoader
  {
    static void png_read_fn(png_structp, png_bytep, size_t);

  public:
    CPrivateImaGLData load(std::istream& is) override;
  };

}

#endif