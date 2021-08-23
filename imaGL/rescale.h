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
  void t_downscale_x(const CPrivateImaGLData& source, CPrivateImaGLData& dest)
  {
    assert(source.width() > dest.width());
    assert(source.height() == dest.height());
    assert(source.pixelFormat() == dest.pixelFormat());
    assert(source.pixelType() == dest.pixelType());
    assert(source.pixelSize() == dest.pixelSize());
    assert(dest.data().size() == dest.height() * dest.width() * dest.pixelSize());
    assert(source.data().size() == source.height() * source.width() * source.pixelSize());

    double dInvScaleFactor = (source.width() - 1) / (double)(dest.width() - 1);
    size_t nInvScaleFactor = (size_t)dInvScaleFactor; //get integer part
#if __cpp_lib_int_pow2 == 202002L
    using std::bit_floor;
#endif // __cpp_lib_int_pow2

    std::int32_t nPrevPowerOf2 = static_cast<std::int32_t>(bit_floor(nInvScaleFactor));

    const CPrivateImaGLData* pSource = &source;
    CPrivateImaGLData temp;

    //Brute mipmaping
    if (nPrevPowerOf2 > 1)
    {
      temp = CPrivateImaGLData(pSource->width() / nPrevPowerOf2, pSource->height(), pSource->pixelFormat(), pSource->pixelType());

      const PixelType* srcPixels = reinterpret_cast<const PixelType*>(pSource->data().data());
      PixelType* destPixels = reinterpret_cast<PixelType*>(temp.data().data());

      for (size_t row = 0; row < temp.height(); ++row)
        for (size_t destCol = 0; destCol < temp.width(); ++destCol)
        {
          assert(row < temp.height() && destCol < temp.width());
          PixelType* destPix = &destPixels[row * temp.width() + destCol];
          typename PixelType::accum_type destPixelAccumulator;
          for (size_t i = 0; i < nPrevPowerOf2; ++i)
          {
            size_t srcCol = destCol * nPrevPowerOf2 + i;
            assert(row < pSource->height() && srcCol < pSource->width());
            destPixelAccumulator += srcPixels[row * pSource->width() + srcCol];
          }
          destPixelAccumulator /= nPrevPowerOf2;
          *destPix = destPixelAccumulator;
        }

      pSource = &temp;
    }

    //Linear Interpolation
    dInvScaleFactor = (pSource->width() - 1) / (double)(dest.width() - 1);
    const PixelType* srcPixels = reinterpret_cast<const PixelType*>(pSource->data().data());
    PixelType* destPixels = reinterpret_cast<PixelType*>(dest.data().data());

    for (size_t row = 0; row < dest.height(); ++row)
      for (size_t destCol = 0; destCol < dest.width(); ++destCol)
      {
        assert(row < dest.height()&& destCol < dest.width());
        PixelType* destPix = &destPixels[row * dest.width() + destCol];
        typename PixelType::accum_type destPixelAccumulator;

        double dDecimalPart = destCol * dInvScaleFactor;
        size_t srcCol = static_cast<size_t>(dDecimalPart);
        dDecimalPart = dDecimalPart - srcCol;

        if (dDecimalPart == 0.0)
        {
          assert(row < pSource->height() && srcCol < pSource->width());
          *destPix = srcPixels[row * pSource->width() + srcCol];
        }
        else
        {
          assert(row < pSource->height() && srcCol + 1 < pSource->width());
          *destPix = srcPixels[row * pSource->width() + srcCol] * (1 - dDecimalPart) + srcPixels[row * pSource->width() + srcCol + 1] * (dDecimalPart);
        }
      }

  }

  _create_fnMap(t_downscale_x);

  inline void downscale_x(const CPrivateImaGLData& source, CPrivateImaGLData& dest)
  {
    assert(source.width() > dest.width());
    assert(source.height() == dest.height());
    assert(source.pixelFormat() == dest.pixelFormat());
    assert(source.pixelType() == dest.pixelType());
    assert(source.pixelSize() == dest.pixelSize());
    assert(dest.data().size() == dest.height() * dest.width() * dest.pixelSize());
    assert(source.data().size() == source.height() * source.width() * source.pixelSize());

    static auto fnMap = create_fnMap(t_downscale_x);

    fnMap[fn_pixel_type_id(source.pixelFormat(), source.pixelType())](source, dest);
  }

  template<typename PixelType>
  void t_downscale_y(const CPrivateImaGLData& source, CPrivateImaGLData& dest)
  {
    assert(source.width() == dest.width());
    assert(source.height() > dest.height());
    assert(source.pixelFormat() == dest.pixelFormat());
    assert(source.pixelType() == dest.pixelType());
    assert(source.pixelSize() == dest.pixelSize());
    assert(dest.data().size() == dest.height() * dest.width() * dest.pixelSize());
    assert(source.data().size() == source.height() * source.width() * source.pixelSize());

    double dInvScaleFactor = (source.height() - 1) / (double)(dest.height() - 1);
    size_t nInvScaleFactor = (size_t)dInvScaleFactor; //get integer part
#if __cpp_lib_int_pow2 == 202002L
    using std::bit_floor;
#endif // __cpp_lib_int_pow2
    std::int32_t nPrevPowerOf2 = static_cast<std::int32_t>(bit_floor(nInvScaleFactor));

    const CPrivateImaGLData* pSource = &source;
    CPrivateImaGLData temp;

    //Brute mipmaping
    if (nPrevPowerOf2 > 1)
    {
      temp = CPrivateImaGLData(pSource->width(), pSource->height() / nPrevPowerOf2, pSource->pixelFormat(), pSource->pixelType());

      const PixelType* srcPixels = reinterpret_cast<const PixelType*>(pSource->data().data());
      PixelType* destPixels = reinterpret_cast<PixelType*>(temp.data().data());

      for (size_t destRow = 0; destRow < temp.height(); ++destRow)
        for (size_t col = 0; col < temp.width(); ++col)
        {
          assert(destRow < temp.height()&& col < temp.width());
          PixelType* destPix = &destPixels[destRow * temp.width() + col];
          typename PixelType::accum_type destPixelAccumulator;
          for (size_t i = 0; i < nPrevPowerOf2; ++i)
          {
            size_t srcRow = destRow * nPrevPowerOf2 + i;
            assert(srcRow < pSource->height()&& col < pSource->width());
            destPixelAccumulator += srcPixels[srcRow * pSource->width() + col];
          }
          destPixelAccumulator /= nPrevPowerOf2;
          *destPix = destPixelAccumulator;
        }

      pSource = &temp;
    }

    //Linear Interpolation
    dInvScaleFactor = (pSource->height() - 1) / (double)(dest.height() - 1);
    const PixelType* srcPixels = reinterpret_cast<const PixelType*>(pSource->data().data());
    PixelType* destPixels = reinterpret_cast<PixelType*>(dest.data().data());

    for (size_t destRow = 0; destRow < dest.height(); ++destRow)
      for (size_t col = 0; col < dest.width(); ++col)
      {
        assert(destRow < dest.height()&& col < dest.width());
        PixelType* destPix = &destPixels[destRow * dest.width() + col];
        typename PixelType::accum_type destPixelAccumulator;

        double dDecimalPart = destRow * dInvScaleFactor;
        size_t srcRow = static_cast<size_t>(dDecimalPart);
        dDecimalPart = dDecimalPart - srcRow;

        if (dDecimalPart == 0.0)
        {
          assert(srcRow < pSource->height() && col < pSource->width());
          *destPix = srcPixels[srcRow * pSource->width() + col];
        }
        else
        {
          assert(srcRow + 1 < pSource->height() && col < pSource->width());
          *destPix = srcPixels[srcRow * pSource->width() + col] * (1 - dDecimalPart) + srcPixels[(srcRow + 1) * pSource->width() + col] * (dDecimalPart);
        }
      }


  }

  _create_fnMap(t_downscale_y);

  inline void downscale_y(const CPrivateImaGLData& source, CPrivateImaGLData& dest)
  {
    assert(source.width() == dest.width());
    assert(source.height() > dest.height());
    assert(source.pixelFormat() == dest.pixelFormat());
    assert(source.pixelType() == dest.pixelType());
    assert(source.pixelSize() == dest.pixelSize());
    assert(dest.data().size() == dest.height() * dest.width() * dest.pixelSize());
    assert(source.data().size() == source.height() * source.width() * source.pixelSize());

    static auto fnMap = create_fnMap(t_downscale_y);

    fnMap[fn_pixel_type_id(source.pixelFormat(), source.pixelType())](source, dest);
  }


  template<typename PixelType>
  void t_upscale_x(const CPrivateImaGLData& source, CPrivateImaGLData& dest)
  {
    assert(source.width() < dest.width());
    assert(source.height() == dest.height());
    assert(source.pixelFormat() == dest.pixelFormat());
    assert(source.pixelType() == dest.pixelType());
    assert(source.pixelSize() == dest.pixelSize());
    assert(dest.data().size() == dest.height() * dest.width() * dest.pixelSize());
    assert(source.data().size() == source.height() * source.width() * source.pixelSize());

    //Linear Interpolation
    double dInvScaleFactor = (source.width() - 1) / (double)(dest.width() - 1);
    const PixelType* srcPixels = reinterpret_cast<const PixelType*>(source.data().data());
    PixelType* destPixels = reinterpret_cast<PixelType*>(dest.data().data());

    for (size_t row = 0; row < dest.height(); ++row)
      for (size_t destCol = 0; destCol < dest.width(); ++destCol)
      {
        assert(row < dest.height() && destCol < dest.width());
        PixelType* destPix = &destPixels[row * dest.width() + destCol];
        typename PixelType::accum_type destPixelAccumulator;

        double dDecimalPart = destCol * dInvScaleFactor;
        size_t srcCol = static_cast<size_t>(dDecimalPart);
        dDecimalPart = dDecimalPart - srcCol;

        if (dDecimalPart == 0.0)
        {
          assert(row < source.height() && srcCol < source.width());
          *destPix = srcPixels[row * source.width() + srcCol];
        }
        else
        {
          assert(row < source.height() && srcCol + 1 < source.width());
          *destPix = srcPixels[row * source.width() + srcCol] * (1 - dDecimalPart) + srcPixels[row * source.width() + srcCol + 1] * (dDecimalPart);
        }
      }


  }

  _create_fnMap(t_upscale_x);

  inline void upscale_x(const CPrivateImaGLData& source, CPrivateImaGLData& dest)
  {
    assert(source.width() < dest.width());
    assert(source.height() == dest.height());
    assert(source.pixelFormat() == dest.pixelFormat());
    assert(source.pixelType() == dest.pixelType());
    assert(source.pixelSize() == dest.pixelSize());
    assert(dest.data().size() == dest.height() * dest.width() * dest.pixelSize());
    assert(source.data().size() == source.height() * source.width() * source.pixelSize());

    static auto fnMap = create_fnMap(t_upscale_x);

    fnMap[fn_pixel_type_id(source.pixelFormat(), source.pixelType())](source, dest);
  }

  template<typename PixelType>
  void t_upscale_y(const CPrivateImaGLData& source, CPrivateImaGLData& dest)
  {
    assert(source.width() == dest.width());
    assert(source.height() < dest.height());
    assert(source.pixelFormat() == dest.pixelFormat());
    assert(source.pixelType() == dest.pixelType());
    assert(source.pixelSize() == dest.pixelSize());
    assert(dest.data().size() == dest.height() * dest.width() * dest.pixelSize());
    assert(source.data().size() == source.height() * source.width() * source.pixelSize());

    //Linear Interpolation
    double dInvScaleFactor = (source.height() - 1) / (double)(dest.height() - 1);
    const PixelType* srcPixels = reinterpret_cast<const PixelType*>(source.data().data());
    PixelType* destPixels = reinterpret_cast<PixelType*>(dest.data().data());

    for (size_t destRow = 0; destRow < dest.height(); ++destRow)
      for (size_t col = 0; col < dest.width(); ++col)
      {
        assert(destRow < dest.height()&& col < dest.width());
        PixelType* destPix = &destPixels[destRow * dest.width() + col];
        typename PixelType::accum_type destPixelAccumulator;

        double dDecimalPart = destRow * dInvScaleFactor;
        size_t srcRow = static_cast<size_t>(dDecimalPart);
        dDecimalPart = dDecimalPart - srcRow;

        if (dDecimalPart == 0.0)
        {
          assert(srcRow < source.height() && col < source.width());
          *destPix = srcPixels[srcRow * source.width() + col];
        }
        else
        {
          assert(srcRow + 1 < source.height() && col < source.width());
          *destPix = srcPixels[srcRow * source.width() + col] * (1 - dDecimalPart) + srcPixels[(srcRow + 1) * source.width() + col] * (dDecimalPart);
        }
      }

  }

  _create_fnMap(t_upscale_y);

  inline void upscale_y(const CPrivateImaGLData& source, CPrivateImaGLData& dest)
  {
    assert(source.width() == dest.width());
    assert(source.height() < dest.height());
    assert(source.pixelFormat() == dest.pixelFormat());
    assert(source.pixelType() == dest.pixelType());
    assert(source.pixelSize() == dest.pixelSize());
    assert(dest.data().size() == dest.height() * dest.width() * dest.pixelSize());
    assert(source.data().size() == source.height() * source.width() * source.pixelSize());

    static auto fnMap = create_fnMap(t_upscale_y);

    fnMap[fn_pixel_type_id(source.pixelFormat(), source.pixelType())](source, dest);
  }


}