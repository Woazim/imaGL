#pragma once
#include <istream>
#include <memory>
#include <stdexcept>

namespace imaGL {

  class CPrivateImaGLData;

  class ILoader
  {
  public:
    virtual CPrivateImaGLData load(std::istream& is) = 0;
  };

}