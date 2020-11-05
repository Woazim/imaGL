#pragma once

#include "imaGL.h"

namespace ImaGL {

  struct SPrivateImaGLData
  {
    std::vector<unsigned char> m_vRawData;
    size_t m_nWidth = 0;
    size_t m_nHeight = 0;
    CImaGL::EPixelFormat m_PixelFormat = CImaGL::EPixelFormat::Undefined;
    CImaGL::EPixelType   m_PixelType = CImaGL::EPixelType::Undefined;
    size_t m_nPixelSize = 0;
  };

}