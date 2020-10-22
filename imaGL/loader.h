#pragma once
#include <istream>
#include <memory>
#include <stdexcept>

namespace ImaGL {

  class bad_format : public ::std::runtime_error {
  public:
    bad_format(const char* message) : ::std::runtime_error(message) {}
  };

  struct SPrivateImaGLData;

  class ILoader
  {
  public:
    virtual SPrivateImaGLData load(std::istream& is) = 0;
  };

}