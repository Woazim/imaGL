#pragma once

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <imaGL/imaGL.h>
#include <catch2/catch.hpp>

template<typename pixel_type>
void test_reading(size_t width, size_t height, const imaGL::CImaGL& img, std::string_view filename)
{
  CHECK(img.width() == width);
  CHECK(img.height() == height);
  CHECK(img.pixelformat() == pixel_type::pixel_format());
  CHECK(img.pixeltype() == pixel_type::pixel_type());
  REQUIRE(img.pixelsize() == pixel_type::pixel_size()); //Here, it is required, otherwise next CHECK will crash

  //read expected pixels data from <filename>.txt
  std::ifstream ifs(std::string(filename) + ".txt");
  std::vector<pixel_type> pixels;
  const size_t nSize = img.width() * img.height();
  pixels.reserve(nSize);
  size_t iComp = 0;
  pixel_type pixel;
  while (!ifs.eof())
  {
    typename pixel_type::comp_type val;
    if constexpr (sizeof(typename pixel_type::comp_type) == 1)
    {
      short valTemp;
      ifs >> valTemp;
      val = static_cast<typename pixel_type::comp_type>(valTemp);
    }
    else
      ifs >> val;
    if (ifs.good())
    {
      pixel.comp_i(iComp, val);
      iComp++;
      iComp %= pixel_type::nb_comp();
      if(iComp == 0)
        pixels.push_back(pixel);
    }
  }
  REQUIRE(pixels.size() == nSize);

  const pixel_type* p1 = pixels.data();
  const pixel_type* p2 = reinterpret_cast<const pixel_type*>(img.pixels());
  size_t i = 0;
  size_t row;
  size_t fliped_row;
  size_t col;
  for (i = 0; i < nSize; ++i)
  {
    row = i / width;
    fliped_row = height - row - 1;
    col = i % width;
    if (p1[row * width + col] != p2[fliped_row * width + col])
    {
      break;
    }
  }
  INFO("Check fails for row = " << row << " col = " << col 
    << ".\nPixel should be " << p1[row * width + col] << " but is " << p2[fliped_row * width + col] 
    << ".\nTest image filename: " << filename);
  CHECK(i == nSize);
}

template<typename PixelType>
void test_readingPixels(std::byte* rawData)
{
  REQUIRE(sizeof(PixelType) == PixelType::pixel_size());
  //Testing with pointer cast
  const PixelType* pPix = reinterpret_cast<const PixelType*>(rawData);
  for (size_t iPix = 0; iPix < 2; ++iPix)
  {
    if constexpr (PixelType::is_packed())
    {
      for (size_t i = 0; i < imaGL::NbComp<PixelType::pixel_format()>::val; ++i)
      {
        using pack_type = typename PixelType::pack_type;
        unsigned long valCompPix = pPix[iPix].comp_i(i);
        unsigned long valCompRaw = ((*reinterpret_cast<typename PixelType::pack_type::type*>(rawData + iPix * PixelType::pixel_size())) & pack_type::componentMasks()[i]) >> pack_type::componentShifts()[i];
        CHECK(valCompPix == valCompRaw);
      }
    }
    else
    {
      for (size_t i = 0; i < imaGL::NbComp<PixelType::pixel_format()>::val; ++i)
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
  std::byte rawData[PixelType::pixel_size() * 2];
  PixelType* pixelForWriting = reinterpret_cast<PixelType*>(rawData);
  const PixelType* pixelForReading = reinterpret_cast<const PixelType*>(rawData);
  for (size_t iPix = 0; iPix < 2; ++iPix)
  {
    if constexpr (PixelType::is_packed())
    {
      for (size_t i = 0; i < imaGL::NbComp<PixelType::pixel_format()>::val; ++i)
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
      for (size_t i = 0; i < imaGL::NbComp<PixelType::pixel_format()>::val; ++i)
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

void export_FITS_file(const imaGL::CImaGL& img, std::string strFileName);

template<typename pixel_type>
void test_img_rescale(const imaGL::CImaGL& img, std::string_view strFileName, std::int32_t width, std::int32_t height)
{
  imaGL::CImaGL img_scaled(img);
  img_scaled.rescale(width, height);

  //This comment is useful if you want to store your results in a file
  //The file is in FITS file format
  std::stringstream ss;
  ss << strFileName << "_" << width << "_" << height << ".fit";
  export_FITS_file(img_scaled, ss.str());

  std::stringstream ss2;
  ss2 << strFileName << "_" << width << "_" << height << ".png";
  test_reading<pixel_type>(width, height, img_scaled, ss2.str());
}