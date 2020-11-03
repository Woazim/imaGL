#pragma once

#include <iostream>
#include <iomanip>
#include <fstream>
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