#pragma once

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "../imaGL/imaGL.h"
#include <catch2/catch.hpp>

template<typename pixel_type>
void test_reading(ImaGL::CImaGL::EPixelFormat pf, ImaGL::CImaGL::EPixelType pt, size_t nNbComponents, size_t width, size_t height, const char* filename)
{
  ImaGL::CImaGL img(filename);

  CHECK(img.width() == width);
  CHECK(img.height() == height);
  CHECK(img.pixelformat() == pf);
  CHECK(img.pixeltype() == pt);
  REQUIRE(img.pixelsize() == nNbComponents*sizeof(pixel_type)); //Here, it is required, otherwise next CHECK will crash

  //read expected pixels data from <filename>.txt
  std::ifstream ifs(std::string(filename) + ".txt");
  std::vector<pixel_type> pixels;
  const size_t nSize = img.width() * img.height() * nNbComponents;
  pixels.reserve(nSize);
  while (!ifs.eof())
  {
    unsigned short val;
    ifs >> val;
    if (ifs.good())
      pixels.push_back(static_cast<pixel_type>(val));
  }
  REQUIRE(pixels.size() == nSize);

  const pixel_type* p1 = pixels.data();
  const pixel_type* p2 = reinterpret_cast<const pixel_type*>(img.pixels());
  size_t i = 0;
  for (i = 0; i < nSize; ++i, ++p1, ++p2)
  {
    if (*p1 != *p2)
    {
      break;
    }
  }
  CHECK(i == nSize);
}

template<typename PixelType>
void test_readingPixels(unsigned char* rawData)
{
  REQUIRE(sizeof(PixelType) == PixelType::pixel_size());
  //Testing with pointer cast
  const PixelType* pPix = reinterpret_cast<const PixelType*>(rawData);
  for (size_t iPix = 0; iPix < 2; ++iPix)
  {
    if constexpr (PixelType::is_packed())
    {
      for (size_t i = 0; i < ImaGL::NbComp<PixelType::pixel_format()>::val; ++i)
      {
        using pack_type = typename PixelType::pack_type;
        unsigned long valCompPix = pPix[iPix].comp_i(i);
        unsigned long valCompRaw = ((*reinterpret_cast<typename PixelType::pack_type::type*>(rawData + iPix * PixelType::pixel_size())) & pack_type::componentMasks()[i]) >> pack_type::componentShifts()[i];
        CHECK(valCompPix == valCompRaw);
      }
    }
    else
    {
      for (size_t i = 0; i < ImaGL::NbComp<PixelType::pixel_format()>::val; ++i)
      {
        unsigned long valCompPix = (unsigned long)pPix[iPix].comp_i(i);
        unsigned long valCompRaw = (unsigned long)*reinterpret_cast<typename PixelType::comp_type*>(rawData + iPix * PixelType::pixel_size() + i * sizeof(typename PixelType::comp_type));
        CHECK(valCompPix == valCompRaw);
      }
    }
  }
}

template<typename PixelType>
void test_writingPixels()
{
  unsigned char rawData[PixelType::pixel_size() * 2];
  PixelType* pixelForWriting = reinterpret_cast<PixelType*>(rawData);
  const PixelType* pixelForReading = reinterpret_cast<const PixelType*>(rawData);
  for (size_t iPix = 0; iPix < 2; ++iPix)
  {
    if constexpr (PixelType::is_packed())
    {
      for (size_t i = 0; i < ImaGL::NbComp<PixelType::pixel_format()>::val; ++i)
      {
        using pack_type = typename PixelType::pack_type;
        typename PixelType::comp_type valCompW = (typename PixelType::comp_type)rand();
        pixelForWriting[iPix].comp_i(i, valCompW);

        typename PixelType::comp_type valCompR;
        valCompR = pixelForReading[iPix].comp_i(i);
        CHECK(((((size_t)valCompW << pack_type::componentShifts()[i]) & pack_type::componentMasks()[i]) >> pack_type::componentShifts()[i]) == valCompR);
      }
    }
    else
    {
      for (size_t i = 0; i < ImaGL::NbComp<PixelType::pixel_format()>::val; ++i)
      {
        typename PixelType::comp_type valCompW = (typename PixelType::comp_type)rand();
        pixelForWriting[iPix].comp_i(i, valCompW);

        typename PixelType::comp_type valCompR;
        valCompR = pixelForReading[iPix].comp_i(i);
        CHECK(valCompW == valCompR);
      }

    }

  }
}

void export_FITS_file(const ImaGL::CImaGL& img, std::string strFileName);
