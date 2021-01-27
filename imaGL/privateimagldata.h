#pragma once

#include "public/imaGL/imaGL.h"

namespace imaGL {

  struct SPrivateImaGLData
  {
    std::vector<std::byte> m_vRawData;
    std::int32_t m_nWidth = 0;
    std::int32_t m_nHeight = 0;
    CImaGL::EPixelFormat m_PixelFormat = CImaGL::EPixelFormat::Undefined;
    CImaGL::EPixelType   m_PixelType = CImaGL::EPixelType::Undefined;
    size_t m_nPixelSize = 0;
  };

  template<typename PixelType>
  long long t_long_component_at(const SPrivateImaGLData& img, size_t row, size_t col, size_t component)
  {
    const PixelType* pPixels = reinterpret_cast<const PixelType*>(img.m_vRawData.data());
    return static_cast<long long>(pPixels[row * img.m_nWidth + col].comp_i(component));
  }

  template<typename PixelType>
  float t_float_component_at(const SPrivateImaGLData& img, size_t row, size_t col, size_t component)
  {
    const PixelType* pPixels = reinterpret_cast<const PixelType*>(img.m_vRawData.data());
    return static_cast<float>(pPixels[row * img.m_nWidth + col].comp_i(component));
  }
}