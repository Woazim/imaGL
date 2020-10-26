// test.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include <imaGL.h>
#include <UnitTest++/UnitTest++.h>


TEST(Openning_16bits_RGBA_PNG_file)
{
  ImaGL::CImaGL img("test-16b.png");

  REQUIRE
  {
    CHECK_EQUAL(256, img.width());
    CHECK_EQUAL(256, img.height());
    CHECK_EQUAL(ImaGL::CImaGL::EPixelFormat::RGBA, img.pixelformat());
    CHECK_EQUAL(ImaGL::CImaGL::EPixelType::UShort, img.pixeltype());
    CHECK_EQUAL(8, img.pixelsize());
  }

    //read expected pixels data from test-16b.rgba
  std::ifstream ifs("test-16b.rgba");
  std::vector<unsigned short> pixels;
  pixels.reserve(256 * 256 * 4);
  while (!ifs.eof())
  {
    unsigned short val;
    ifs >> val;
    if (ifs.good())
      pixels.push_back(val);
  }

  CHECK_ARRAY_EQUAL(pixels.data(), reinterpret_cast<const unsigned short*>(img.pixels()), 256 * 256 * 4);
}

TEST(Openning_8bits_RGBA_PNG_file)
{
  ImaGL::CImaGL img("test-8b.png");

  REQUIRE
  {
    CHECK_EQUAL(256, img.width());
    CHECK_EQUAL(256, img.height());
    CHECK_EQUAL(ImaGL::CImaGL::EPixelFormat::RGBA, img.pixelformat());
    CHECK_EQUAL(ImaGL::CImaGL::EPixelType::UByte, img.pixeltype());
    CHECK_EQUAL(4, img.pixelsize());
  }

    //read expected pixels data from test-16b.rgba
  std::ifstream ifs("test-8b.rgba");
  std::vector<unsigned char> pixels;
  pixels.reserve(256 * 256 * 4);
  while (!ifs.eof())
  {
    unsigned int val; //use int here to avoid to consider char as real characters
    ifs >> val;
    if (ifs.good())
      pixels.push_back(val);
  }

  CHECK_ARRAY_EQUAL(pixels.data(), img.pixels(), 256 * 256 * 4);
}

int main()
{
  std::cout << "Test ImaGL\n";

  return UnitTest::RunAllTests();
}

