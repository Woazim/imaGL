// test.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//
#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() 

#include <iostream>
#include <iomanip>
#include <fstream>
#include "../imaGL/imaGL.h"
#include <catch2/catch.hpp>


TEST_CASE("Opening a 16 bits RGBA PNG file", "[test-16b]")
{
  ImaGL::CImaGL img("test-16b.png");

  CHECK(img.width() == 256);
  CHECK(img.height() == 256);
  CHECK(img.pixelformat() == ImaGL::CImaGL::EPixelFormat::RGBA);
  CHECK(img.pixeltype() == ImaGL::CImaGL::EPixelType::UShort);
  REQUIRE(img.pixelsize() == 8); //Here, it is required, otherwise next CHECK will crash

  //read expected pixels data from test-16b.rgba
  std::ifstream ifs("test-16b.rgba");
  std::vector<unsigned short> pixels;
  const size_t nSize = img.width() * img.height() * 4;
  pixels.reserve(nSize);
  while (!ifs.eof())
  {
    unsigned short val;
    ifs >> val;
    if (ifs.good())
      pixels.push_back(val);
  }
  const unsigned short* p1 = pixels.data();
  const unsigned short* p2 = reinterpret_cast<const unsigned short*>(img.pixels());
  size_t i = 0;
  for (i = 0; i < nSize; ++i, ++p1, ++p2)
  {
    if (*p1 != *p2)
    {
      break;
    }
  }
  CHECK(i == nSize);

  //CHECK_THAT(pixels, Catch::Matchers::Equals(std::vector<unsigned short>(reinterpret_cast<const unsigned short*>(img.pixels()), reinterpret_cast<const unsigned short*>(img.pixels()) + nSize)));
}

TEST_CASE("Opening a 8 bits RGBA PNG file", "[test-8b]")
{
  ImaGL::CImaGL img("test-8b.png");

  CHECK(img.width() == 256);
  CHECK(img.height() == 256);
  CHECK(img.pixelformat() == ImaGL::CImaGL::EPixelFormat::RGBA);
  CHECK(img.pixeltype() == ImaGL::CImaGL::EPixelType::UByte);
  REQUIRE(img.pixelsize() == 4); //Here, it is required, otherwise next CHECK will crash

  //read expected pixels data from test-8b.rgba
  std::ifstream ifs("test-8b.rgba");
  std::vector<unsigned char> pixels;
  const size_t nSize = img.width() * img.height() * 4;
  pixels.reserve(nSize);
  while (!ifs.eof())
  {
    unsigned int val; //use int here to avoid to consider char as real characters
    ifs >> val;
    if (ifs.good())
      pixels.push_back(val);
  }

  const unsigned char* p1 = pixels.data();
  const unsigned char* p2 = img.pixels();
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

