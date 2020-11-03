#pragma once
#include "loader.h"
#include "imaGL.h"

#ifdef _HAS_PNG
#include <png.h>

namespace ImaGL {

  class CLoaderPNG :
    public ILoader
  {
    CImaGL::EPixelFormat m_pf = CImaGL::EPixelFormat::Undefined;
    CImaGL::EPixelType m_pt = CImaGL::EPixelType::Undefined;

    static void png_read_fn(png_structp, png_bytep, size_t);

  public:
    SPrivateImaGLData load(std::istream& is) override;
  };

}

#endif