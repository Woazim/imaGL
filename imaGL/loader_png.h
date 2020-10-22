#pragma once
#include "loader.h"
#include "imagl_cfg.h"

#ifdef _HAS_LIBPNG

namespace ImaGL {

  class CLoaderPNG :
    public ILoader
  {
    SPrivateImaGLData load(std::istream& is) override;
  };

}

#endif