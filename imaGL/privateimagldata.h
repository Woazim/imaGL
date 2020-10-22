#pragma once

#include "imaGL.h"

namespace ImaGL {

  struct SPrivateImaGLData
  {
    std::vector<unsigned char> m_vRawData;
    int m_nWidth = 0;
    int m_nHeight = 0;
    CImaGL::EPixelFormat m_PixelFormat = CImaGL::EPixelFormat::Undefined;
    CImaGL::EPixelType   m_PixelType = CImaGL::EPixelType::Undefined;
  };

}