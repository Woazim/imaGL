#pragma once
#include <map>

namespace ImaGL {

  template<typename PixelType>
  void t_downscale_x(const SPrivateImaGLData& source, SPrivateImaGLData& dest)
  {
    assert(source.m_nWidth > dest.m_nWidth);
    assert(source.m_nHeight == dest.m_nHeight);
    assert(source.m_PixelFormat == dest.m_PixelFormat);
    assert(source.m_PixelType == dest.m_PixelType);
    assert(source.m_nPixelSize == dest.m_nPixelSize);
    assert(dest.m_vRawData.size() == dest.m_nHeight * dest.m_nWidth * dest.m_nPixelSize);
    assert(source.m_vRawData.size() == source.m_nHeight * source.m_nWidth * source.m_nPixelSize);

    double dInvScaleFactor = source.m_nWidth / (double)dest.m_nWidth;
    size_t nInvScaleFactor = (size_t)dInvScaleFactor; //get integer part
    size_t nPrevPowerOf2 = 0;
    for (size_t nMask = (((size_t)1) << (sizeof(size_t) * 8 - 1));
      nPrevPowerOf2 == 0 && nMask != 0;
      nMask >>= 1
      )
    {
      nPrevPowerOf2 = nInvScaleFactor & nMask;
    }

    const SPrivateImaGLData* pSource = &source;
    SPrivateImaGLData temp;

    //Brute mipmaping
    if (nPrevPowerOf2 > 1)
    {
      temp.m_nHeight = source.m_nHeight;
      temp.m_nWidth = source.m_nWidth / nPrevPowerOf2;
      temp.m_nPixelSize = source.m_nPixelSize;
      temp.m_PixelFormat = source.m_PixelFormat;
      temp.m_PixelType = source.m_PixelType;
      temp.m_vRawData = std::vector<unsigned char>(temp.m_nHeight * temp.m_nWidth * temp.m_nPixelSize);

      const PixelType* srcPixels = reinterpret_cast<const PixelType*>(source.m_vRawData.data());
      PixelType* destPixels = reinterpret_cast<PixelType*>(temp.m_vRawData.data());

      for (size_t row = 0; row < temp.m_nHeight; ++row)
        for (size_t destCol = 0; destCol < temp.m_nWidth; ++destCol)
        {
          PixelType* destPix = &destPixels[row * temp.m_nWidth + destCol];
          typename PixelType::accum_type destPixelAccumulator;
          for (size_t i = 0; i < nPrevPowerOf2; ++i)
          {
            size_t srcCol = destCol * nPrevPowerOf2 + i;
            destPixelAccumulator += srcPixels[row * source.m_nWidth + srcCol];
          }
          destPixelAccumulator /= nPrevPowerOf2;
          *destPix = destPixelAccumulator;
        }

      pSource = &temp;
    }

    //Linear Interpolation
    dInvScaleFactor = pSource->m_nWidth / (double)dest.m_nWidth;
    const PixelType* srcPixels = reinterpret_cast<const PixelType*>(pSource->m_vRawData.data());
    PixelType* destPixels = reinterpret_cast<PixelType*>(dest.m_vRawData.data());

    for (size_t row = 0; row < pSource->m_nHeight; ++row)
      for (size_t destCol = 0; destCol < dest.m_nWidth; ++destCol)
      {
        PixelType* destPix = &destPixels[row * dest.m_nWidth + destCol];
        typename PixelType::accum_type destPixelAccumulator;

        double dDecimalPart = destCol * dInvScaleFactor;
        size_t srcCol = static_cast<size_t>(dDecimalPart);
        dDecimalPart = dDecimalPart - srcCol;

        *destPix = srcPixels[row * pSource->m_nWidth + srcCol] * (1-dDecimalPart) + srcPixels[row * pSource->m_nWidth + srcCol + 1] * ( dDecimalPart);
      }


  }

  _create_fnMap(t_downscale_x)

  void downscale_x(const SPrivateImaGLData& source, SPrivateImaGLData& dest)
  {
    assert(source.m_nWidth > dest.m_nWidth);
    assert(source.m_nHeight == dest.m_nHeight);
    assert(source.m_PixelFormat == dest.m_PixelFormat);
    assert(source.m_PixelType == dest.m_PixelType);
    assert(source.m_nPixelSize == dest.m_nPixelSize);
    assert(dest.m_vRawData.size() == dest.m_nHeight * dest.m_nWidth * dest.m_nPixelSize);
    assert(source.m_vRawData.size() == source.m_nHeight * source.m_nWidth * source.m_nPixelSize);

    static std::map<unsigned int, decltype(downscale_x)*> functionMap;

    if (functionMap.empty()) //at first run
    {
      functionMap = create_fnMap(t_downscale_x);
    }

    functionMap[fn_pixel_type_id(source.m_PixelFormat, source.m_PixelType)](source, dest);
  }

}