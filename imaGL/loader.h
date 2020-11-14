#pragma once
#include <istream>
#include <memory>
#include <stdexcept>

namespace imaGL {

  struct SPrivateImaGLData;

  class ILoader
  {
  public:
    virtual SPrivateImaGLData load(std::istream& is) = 0;
  };

}