#pragma once
#include <map>
#if __cpp_lib_int_pow2 == 202002L
#include <bit>
#endif // __cpp_lib_int_pow2

namespace imaGL {

#if __cpp_lib_int_pow2 != 202002L
  template<typename T>
  T bit_ceil(T x)
  {
    static_assert(std::is_integral_v<T> && std::is_unsigned_v<T>);
    --x;
    T ret = 1;
    while (x != 0)
    {
      x >>= 1;
      ret <<= 1;
    }
    return ret;
  }

  template<typename T>
  T bit_floor(T x)
  {
    static_assert(std::is_integral_v<T> && std::is_unsigned_v<T>);
    if (x == 0)
      return 0;
    else
    {
      T ret = 1;
      while (x != 1)
      {
        x >>= 1; ret <<= 1;
      }
      return ret;
    }
  }
#endif // !__cpp_lib_int_pow2

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

    double dInvScaleFactor = (source.m_nWidth - 1) / (double)(dest.m_nWidth - 1);
    size_t nInvScaleFactor = (size_t)dInvScaleFactor; //get integer part
#if __cpp_lib_int_pow2 == 202002L
    using std::bit_floor;
#endif // __cpp_lib_int_pow2

    std::int32_t nPrevPowerOf2 = static_cast<std::int32_t>(bit_floor(nInvScaleFactor));

    const SPrivateImaGLData* pSource = &source;
    SPrivateImaGLData temp;

    //Brute mipmaping
    if (nPrevPowerOf2 > 1)
    {
      temp.m_nHeight = pSource->m_nHeight;
      temp.m_nWidth = pSource->m_nWidth / nPrevPowerOf2;
      temp.m_nPixelSize = pSource->m_nPixelSize;
      temp.m_PixelFormat = pSource->m_PixelFormat;
      temp.m_PixelType = pSource->m_PixelType;
      temp.m_vRawData = std::vector<std::byte>(temp.m_nHeight * temp.m_nWidth * temp.m_nPixelSize);

      const PixelType* srcPixels = reinterpret_cast<const PixelType*>(pSource->m_vRawData.data());
      PixelType* destPixels = reinterpret_cast<PixelType*>(temp.m_vRawData.data());

      for (size_t row = 0; row < temp.m_nHeight; ++row)
        for (size_t destCol = 0; destCol < temp.m_nWidth; ++destCol)
        {
          assert(row < temp.m_nHeight && destCol < temp.m_nWidth);
          PixelType* destPix = &destPixels[row * temp.m_nWidth + destCol];
          typename PixelType::accum_type destPixelAccumulator;
          for (size_t i = 0; i < nPrevPowerOf2; ++i)
          {
            size_t srcCol = destCol * nPrevPowerOf2 + i;
            assert(row < pSource->m_nHeight && srcCol < pSource->m_nWidth);
            destPixelAccumulator += srcPixels[row * pSource->m_nWidth + srcCol];
          }
          destPixelAccumulator /= nPrevPowerOf2;
          *destPix = destPixelAccumulator;
        }

      pSource = &temp;
    }

    //Linear Interpolation
    dInvScaleFactor = (pSource->m_nWidth - 1) / (double)(dest.m_nWidth - 1);
    const PixelType* srcPixels = reinterpret_cast<const PixelType*>(pSource->m_vRawData.data());
    PixelType* destPixels = reinterpret_cast<PixelType*>(dest.m_vRawData.data());

    for (size_t row = 0; row < dest.m_nHeight; ++row)
      for (size_t destCol = 0; destCol < dest.m_nWidth; ++destCol)
      {
        assert(row < dest.m_nHeight&& destCol < dest.m_nWidth);
        PixelType* destPix = &destPixels[row * dest.m_nWidth + destCol];
        typename PixelType::accum_type destPixelAccumulator;

        double dDecimalPart = destCol * dInvScaleFactor;
        size_t srcCol = static_cast<size_t>(dDecimalPart);
        dDecimalPart = dDecimalPart - srcCol;

        if (dDecimalPart == 0.0)
        {
          assert(row < pSource->m_nHeight && srcCol < pSource->m_nWidth);
          *destPix = srcPixels[row * pSource->m_nWidth + srcCol];
        }
        else
        {
          assert(row < pSource->m_nHeight && srcCol + 1 < pSource->m_nWidth);
          *destPix = srcPixels[row * pSource->m_nWidth + srcCol] * (1 - dDecimalPart) + srcPixels[row * pSource->m_nWidth + srcCol + 1] * (dDecimalPart);
        }
      }

  }

  _create_fnMap(t_downscale_x);

  inline void downscale_x(const SPrivateImaGLData& source, SPrivateImaGLData& dest)
  {
    assert(source.m_nWidth > dest.m_nWidth);
    assert(source.m_nHeight == dest.m_nHeight);
    assert(source.m_PixelFormat == dest.m_PixelFormat);
    assert(source.m_PixelType == dest.m_PixelType);
    assert(source.m_nPixelSize == dest.m_nPixelSize);
    assert(dest.m_vRawData.size() == dest.m_nHeight * dest.m_nWidth * dest.m_nPixelSize);
    assert(source.m_vRawData.size() == source.m_nHeight * source.m_nWidth * source.m_nPixelSize);

    static auto fnMap = create_fnMap(t_downscale_x);

    fnMap[fn_pixel_type_id(source.m_PixelFormat, source.m_PixelType)](source, dest);
  }

  template<typename PixelType>
  void t_downscale_y(const SPrivateImaGLData& source, SPrivateImaGLData& dest)
  {
    assert(source.m_nWidth == dest.m_nWidth);
    assert(source.m_nHeight > dest.m_nHeight);
    assert(source.m_PixelFormat == dest.m_PixelFormat);
    assert(source.m_PixelType == dest.m_PixelType);
    assert(source.m_nPixelSize == dest.m_nPixelSize);
    assert(dest.m_vRawData.size() == dest.m_nHeight * dest.m_nWidth * dest.m_nPixelSize);
    assert(source.m_vRawData.size() == source.m_nHeight * source.m_nWidth * source.m_nPixelSize);

    double dInvScaleFactor = (source.m_nHeight - 1) / (double)(dest.m_nHeight - 1);
    size_t nInvScaleFactor = (size_t)dInvScaleFactor; //get integer part
#if __cpp_lib_int_pow2 == 202002L
    using std::bit_floor;
#endif // __cpp_lib_int_pow2
    std::int32_t nPrevPowerOf2 = static_cast<std::int32_t>(bit_floor(nInvScaleFactor));

    const SPrivateImaGLData* pSource = &source;
    SPrivateImaGLData temp;

    //Brute mipmaping
    if (nPrevPowerOf2 > 1)
    {
      temp.m_nHeight = pSource->m_nHeight / nPrevPowerOf2;
      temp.m_nWidth = pSource->m_nWidth;
      temp.m_nPixelSize = pSource->m_nPixelSize;
      temp.m_PixelFormat = pSource->m_PixelFormat;
      temp.m_PixelType = pSource->m_PixelType;
      temp.m_vRawData = std::vector<std::byte>(temp.m_nHeight * temp.m_nWidth * temp.m_nPixelSize);

      const PixelType* srcPixels = reinterpret_cast<const PixelType*>(pSource->m_vRawData.data());
      PixelType* destPixels = reinterpret_cast<PixelType*>(temp.m_vRawData.data());

      for (size_t destRow = 0; destRow < temp.m_nHeight; ++destRow)
        for (size_t col = 0; col < temp.m_nWidth; ++col)
        {
          assert(destRow < temp.m_nHeight&& col < temp.m_nWidth);
          PixelType* destPix = &destPixels[destRow * temp.m_nWidth + col];
          typename PixelType::accum_type destPixelAccumulator;
          for (size_t i = 0; i < nPrevPowerOf2; ++i)
          {
            size_t srcRow = destRow * nPrevPowerOf2 + i;
            assert(srcRow < pSource->m_nHeight&& col < pSource->m_nWidth);
            destPixelAccumulator += srcPixels[srcRow * pSource->m_nWidth + col];
          }
          destPixelAccumulator /= nPrevPowerOf2;
          *destPix = destPixelAccumulator;
        }

      pSource = &temp;
    }

    //Linear Interpolation
    dInvScaleFactor = (pSource->m_nHeight - 1) / (double)(dest.m_nHeight - 1);
    const PixelType* srcPixels = reinterpret_cast<const PixelType*>(pSource->m_vRawData.data());
    PixelType* destPixels = reinterpret_cast<PixelType*>(dest.m_vRawData.data());

    for (size_t destRow = 0; destRow < dest.m_nHeight; ++destRow)
      for (size_t col = 0; col < dest.m_nWidth; ++col)
      {
        assert(destRow < dest.m_nHeight&& col < dest.m_nWidth);
        PixelType* destPix = &destPixels[destRow * dest.m_nWidth + col];
        typename PixelType::accum_type destPixelAccumulator;

        double dDecimalPart = destRow * dInvScaleFactor;
        size_t srcRow = static_cast<size_t>(dDecimalPart);
        dDecimalPart = dDecimalPart - srcRow;

        if (dDecimalPart == 0.0)
        {
          assert(srcRow < pSource->m_nHeight && col < pSource->m_nWidth);
          *destPix = srcPixels[srcRow * pSource->m_nWidth + col];
        }
        else
        {
          assert(srcRow + 1 < pSource->m_nHeight && col < pSource->m_nWidth);
          *destPix = srcPixels[srcRow * pSource->m_nWidth + col] * (1 - dDecimalPart) + srcPixels[(srcRow + 1) * pSource->m_nWidth + col] * (dDecimalPart);
        }
      }


  }

  _create_fnMap(t_downscale_y);

  inline void downscale_y(const SPrivateImaGLData& source, SPrivateImaGLData& dest)
  {
    assert(source.m_nWidth == dest.m_nWidth);
    assert(source.m_nHeight > dest.m_nHeight);
    assert(source.m_PixelFormat == dest.m_PixelFormat);
    assert(source.m_PixelType == dest.m_PixelType);
    assert(source.m_nPixelSize == dest.m_nPixelSize);
    assert(dest.m_vRawData.size() == dest.m_nHeight * dest.m_nWidth * dest.m_nPixelSize);
    assert(source.m_vRawData.size() == source.m_nHeight * source.m_nWidth * source.m_nPixelSize);

    static auto fnMap = create_fnMap(t_downscale_y);

    fnMap[fn_pixel_type_id(source.m_PixelFormat, source.m_PixelType)](source, dest);
  }


  template<typename PixelType>
  void t_upscale_x(const SPrivateImaGLData& source, SPrivateImaGLData& dest)
  {
    assert(source.m_nWidth < dest.m_nWidth);
    assert(source.m_nHeight == dest.m_nHeight);
    assert(source.m_PixelFormat == dest.m_PixelFormat);
    assert(source.m_PixelType == dest.m_PixelType);
    assert(source.m_nPixelSize == dest.m_nPixelSize);
    assert(dest.m_vRawData.size() == dest.m_nHeight * dest.m_nWidth * dest.m_nPixelSize);
    assert(source.m_vRawData.size() == source.m_nHeight * source.m_nWidth * source.m_nPixelSize);

    //Linear Interpolation
    double dInvScaleFactor = (source.m_nWidth - 1) / (double)(dest.m_nWidth - 1);
    const PixelType* srcPixels = reinterpret_cast<const PixelType*>(source.m_vRawData.data());
    PixelType* destPixels = reinterpret_cast<PixelType*>(dest.m_vRawData.data());

    for (size_t row = 0; row < dest.m_nHeight; ++row)
      for (size_t destCol = 0; destCol < dest.m_nWidth; ++destCol)
      {
        assert(row < dest.m_nHeight && destCol < dest.m_nWidth);
        PixelType* destPix = &destPixels[row * dest.m_nWidth + destCol];
        typename PixelType::accum_type destPixelAccumulator;

        double dDecimalPart = destCol * dInvScaleFactor;
        size_t srcCol = static_cast<size_t>(dDecimalPart);
        dDecimalPart = dDecimalPart - srcCol;

        if (dDecimalPart == 0.0)
        {
          assert(row < source.m_nHeight && srcCol < source.m_nWidth);
          *destPix = srcPixels[row * source.m_nWidth + srcCol];
        }
        else
        {
          assert(row < source.m_nHeight && srcCol + 1 < source.m_nWidth);
          *destPix = srcPixels[row * source.m_nWidth + srcCol] * (1 - dDecimalPart) + srcPixels[row * source.m_nWidth + srcCol + 1] * (dDecimalPart);
        }
      }


  }

  _create_fnMap(t_upscale_x);

  inline void upscale_x(const SPrivateImaGLData& source, SPrivateImaGLData& dest)
  {
    assert(source.m_nWidth < dest.m_nWidth);
    assert(source.m_nHeight == dest.m_nHeight);
    assert(source.m_PixelFormat == dest.m_PixelFormat);
    assert(source.m_PixelType == dest.m_PixelType);
    assert(source.m_nPixelSize == dest.m_nPixelSize);
    assert(dest.m_vRawData.size() == dest.m_nHeight * dest.m_nWidth * dest.m_nPixelSize);
    assert(source.m_vRawData.size() == source.m_nHeight * source.m_nWidth * source.m_nPixelSize);

    static auto fnMap = create_fnMap(t_upscale_x);

    fnMap[fn_pixel_type_id(source.m_PixelFormat, source.m_PixelType)](source, dest);
  }

  template<typename PixelType>
  void t_upscale_y(const SPrivateImaGLData& source, SPrivateImaGLData& dest)
  {
    assert(source.m_nWidth == dest.m_nWidth);
    assert(source.m_nHeight < dest.m_nHeight);
    assert(source.m_PixelFormat == dest.m_PixelFormat);
    assert(source.m_PixelType == dest.m_PixelType);
    assert(source.m_nPixelSize == dest.m_nPixelSize);
    assert(dest.m_vRawData.size() == dest.m_nHeight * dest.m_nWidth * dest.m_nPixelSize);
    assert(source.m_vRawData.size() == source.m_nHeight * source.m_nWidth * source.m_nPixelSize);

    //Linear Interpolation
    double dInvScaleFactor = (source.m_nHeight - 1) / (double)(dest.m_nHeight - 1);
    const PixelType* srcPixels = reinterpret_cast<const PixelType*>(source.m_vRawData.data());
    PixelType* destPixels = reinterpret_cast<PixelType*>(dest.m_vRawData.data());

    for (size_t destRow = 0; destRow < dest.m_nHeight; ++destRow)
      for (size_t col = 0; col < dest.m_nWidth; ++col)
      {
        assert(destRow < dest.m_nHeight&& col < dest.m_nWidth);
        PixelType* destPix = &destPixels[destRow * dest.m_nWidth + col];
        typename PixelType::accum_type destPixelAccumulator;

        double dDecimalPart = destRow * dInvScaleFactor;
        size_t srcRow = static_cast<size_t>(dDecimalPart);
        dDecimalPart = dDecimalPart - srcRow;

        if (dDecimalPart == 0.0)
        {
          assert(srcRow < source.m_nHeight && col < source.m_nWidth);
          *destPix = srcPixels[srcRow * source.m_nWidth + col];
        }
        else
        {
          assert(srcRow + 1 < source.m_nHeight && col < source.m_nWidth);
          *destPix = srcPixels[srcRow * source.m_nWidth + col] * (1 - dDecimalPart) + srcPixels[(srcRow + 1) * source.m_nWidth + col] * (dDecimalPart);
        }
      }

  }

  _create_fnMap(t_upscale_y);

  inline void upscale_y(const SPrivateImaGLData& source, SPrivateImaGLData& dest)
  {
    assert(source.m_nWidth == dest.m_nWidth);
    assert(source.m_nHeight < dest.m_nHeight);
    assert(source.m_PixelFormat == dest.m_PixelFormat);
    assert(source.m_PixelType == dest.m_PixelType);
    assert(source.m_nPixelSize == dest.m_nPixelSize);
    assert(dest.m_vRawData.size() == dest.m_nHeight * dest.m_nWidth * dest.m_nPixelSize);
    assert(source.m_vRawData.size() == source.m_nHeight * source.m_nWidth * source.m_nPixelSize);

    static auto fnMap = create_fnMap(t_upscale_y);

    fnMap[fn_pixel_type_id(source.m_PixelFormat, source.m_PixelType)](source, dest);
  }


}