#pragma once

#include "public/imaGL/imaGL.h"

namespace imaGL {

  class CPrivateImaGLData
  {
    std::vector<std::byte> m_vRawData;
    std::int32_t m_nWidth = 0;
    std::int32_t m_nHeight = 0;
    CImaGL::EPixelFormat m_PixelFormat = CImaGL::EPixelFormat::Undefined;
    CImaGL::EPixelType   m_PixelType = CImaGL::EPixelType::Undefined;
    size_t m_nPixelSize = 0;


  public:
    CPrivateImaGLData() = default;
    CPrivateImaGLData(const CPrivateImaGLData&) = default;
    CPrivateImaGLData& operator=(const CPrivateImaGLData&) = default;
    CPrivateImaGLData(std::int32_t width, std::int32_t height, CImaGL::EPixelFormat pf, CImaGL::EPixelType pt)
      : m_nWidth(width)
      , m_nHeight(height)
      , m_PixelFormat(pf)
      , m_PixelType(pt)
    {
      m_nPixelSize = computePixelSize(pf, pt);
      m_vRawData.resize(m_nWidth * m_nHeight * m_nPixelSize);
    }

    CPrivateImaGLData(CPrivateImaGLData&& other)
      : m_nWidth(other.m_nWidth)
      , m_nHeight(other.m_nHeight)
      , m_PixelFormat(other.m_PixelFormat)
      , m_PixelType(other.m_PixelType)
      , m_nPixelSize(other.m_nPixelSize)
      , m_vRawData(std::move(other.m_vRawData))
    {
      other.m_nWidth = other.m_nHeight = 0;
      other.m_nPixelSize = 0;
      other.m_PixelFormat = CImaGL::EPixelFormat::Undefined;
      other.m_PixelType = CImaGL::EPixelType::Undefined;
    }

    CPrivateImaGLData& operator=(CPrivateImaGLData&& other) {
      if (&other != this)
      {
        m_nWidth = other.m_nWidth;
        m_nHeight = other.m_nHeight;
        m_PixelFormat = other.m_PixelFormat;
        m_PixelType = other.m_PixelType;
        m_nPixelSize = other.m_nPixelSize;
        m_vRawData = std::move(other.m_vRawData);
        other.m_nWidth = other.m_nHeight = 0;
        other.m_nPixelSize = 0;
        other.m_PixelFormat = CImaGL::EPixelFormat::Undefined;
        other.m_PixelType = CImaGL::EPixelType::Undefined;
      }
      return *this;
    }

    //getters
    const std::vector<std::byte>& data()        const { return m_vRawData; }
    std::vector<std::byte>&       data()              { return m_vRawData; }
    std::int32_t                  width()       const { return m_nWidth; }
    std::int32_t                  height()      const { return m_nHeight; }
    CImaGL::EPixelFormat          pixelFormat() const { return m_PixelFormat; }
    CImaGL::EPixelType            pixelType()   const { return m_PixelType; }
    size_t                        pixelSize()   const { return m_nPixelSize; }
  };

  template<typename PixelType>
  long long t_long_component_at(const CPrivateImaGLData& img, size_t row, size_t col, size_t component)
  {
    const PixelType* pPixels = reinterpret_cast<const PixelType*>(img.data().data());
    return static_cast<long long>(pPixels[row * img.width() + col].comp_i(component));
  }

  template<typename PixelType>
  float t_float_component_at(const CPrivateImaGLData& img, size_t row, size_t col, size_t component)
  {
    const PixelType* pPixels = reinterpret_cast<const PixelType*>(img.data().data());
    return static_cast<float>(pPixels[row * img.width() + col].comp_i(component));
  }
}