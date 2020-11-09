// test.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//
#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() 

#include "test.h"
#include <sstream>

//interlaced cases
TEST_CASE("Opening a 1 bit Gray interlaced PNG file", "[basi0g01]")
{
  test_reading<unsigned char>(ImaGL::CImaGL::EPixelFormat::R, ImaGL::CImaGL::EPixelType::UByte, 1, 32, 32, "basi0g01.png");
}

TEST_CASE("Opening a 2 bits Gray interlaced PNG file", "[basi0g02]")
{
  test_reading<unsigned char>(ImaGL::CImaGL::EPixelFormat::R, ImaGL::CImaGL::EPixelType::UByte, 1, 32, 32, "basi0g02.png");
}

TEST_CASE("Opening a 4 bits Gray interlaced PNG file", "[basi0g04]")
{
  test_reading<unsigned char>(ImaGL::CImaGL::EPixelFormat::R, ImaGL::CImaGL::EPixelType::UByte, 1, 32, 32, "basi0g04.png");
}

TEST_CASE("Opening a 8 bits Gray interlaced PNG file", "[basi0g08]")
{
  test_reading<unsigned char>(ImaGL::CImaGL::EPixelFormat::R, ImaGL::CImaGL::EPixelType::UByte, 1, 32, 32, "basi0g08.png");
}

TEST_CASE("Opening a 16 bits Gray interlaced PNG file", "[basi0g16]")
{
  test_reading<unsigned short>(ImaGL::CImaGL::EPixelFormat::R, ImaGL::CImaGL::EPixelType::UShort, 1, 32, 32, "basi0g16.png");
}

TEST_CASE("Opening a 8 bits Color interlaced PNG file", "[basi2c08]")
{
  test_reading<unsigned char>(ImaGL::CImaGL::EPixelFormat::RGB, ImaGL::CImaGL::EPixelType::UByte, 3, 32, 32, "basi2c08.png");
}

TEST_CASE("Opening a 16 bits Color interlaced PNG file", "[basi2c16]")
{
  test_reading<unsigned short>(ImaGL::CImaGL::EPixelFormat::RGB, ImaGL::CImaGL::EPixelType::UShort, 3, 32, 32, "basi2c16.png");
}

TEST_CASE("Opening a 1 bit Paletted interlaced PNG file", "[basi3p01]")
{
  test_reading<unsigned char>(ImaGL::CImaGL::EPixelFormat::RGB, ImaGL::CImaGL::EPixelType::UByte, 3, 32, 32, "basi3p01.png");
}

TEST_CASE("Opening a 4 bits Paletted interlaced PNG file", "[basi3p04]")
{
  test_reading<unsigned char>(ImaGL::CImaGL::EPixelFormat::RGB, ImaGL::CImaGL::EPixelType::UByte, 3, 32, 32, "basi3p04.png");
}

TEST_CASE("Opening a 8 bits Paletted interlaced PNG file", "[basi3p08]")
{
  test_reading<unsigned char>(ImaGL::CImaGL::EPixelFormat::RGB, ImaGL::CImaGL::EPixelType::UByte, 3, 32, 32, "basi3p08.png");
}

TEST_CASE("Opening a 8 bits Gray + 8 bits Alpha interlaced PNG file", "[basi4a08]")
{
  test_reading<unsigned char>(ImaGL::CImaGL::EPixelFormat::RG, ImaGL::CImaGL::EPixelType::UByte, 2, 32, 32, "basi4a08.png");
}

TEST_CASE("Opening a 16 bits Gray + 16 bits Alpha interlaced PNG file", "[basi4a16]")
{
  test_reading<unsigned short>(ImaGL::CImaGL::EPixelFormat::RG, ImaGL::CImaGL::EPixelType::UShort, 2, 32, 32, "basi4a16.png");
}

TEST_CASE("Opening a 8 bits Color + 8 bits Alpha interlaced PNG file", "[basi6a08]")
{
  test_reading<unsigned char>(ImaGL::CImaGL::EPixelFormat::RGBA, ImaGL::CImaGL::EPixelType::UByte, 4, 32, 32, "basi6a08.png");
}

TEST_CASE("Opening a 16 bits Color + 16 bits Alpha interlaced PNG file", "[basi6a16]")
{
  test_reading<unsigned short>(ImaGL::CImaGL::EPixelFormat::RGBA, ImaGL::CImaGL::EPixelType::UShort, 4, 32, 32, "basi6a16.png");
}



//non interlaced cases
TEST_CASE("Opening a 1 bit Gray PNG file", "[basn0g01]")
{
  test_reading<unsigned char>(ImaGL::CImaGL::EPixelFormat::R, ImaGL::CImaGL::EPixelType::UByte, 1, 32, 32, "basn0g01.png");
}

TEST_CASE("Opening a 2 bits Gray PNG file", "[basn0g02]")
{
  test_reading<unsigned char>(ImaGL::CImaGL::EPixelFormat::R, ImaGL::CImaGL::EPixelType::UByte, 1, 32, 32, "basn0g02.png");
}

TEST_CASE("Opening a 4 bits Gray PNG file", "[basn0g04]")
{
  test_reading<unsigned char>(ImaGL::CImaGL::EPixelFormat::R, ImaGL::CImaGL::EPixelType::UByte, 1, 32, 32, "basn0g04.png");
}

TEST_CASE("Opening a 8 bits Gray PNG file", "[basn0g08]")
{
  test_reading<unsigned char>(ImaGL::CImaGL::EPixelFormat::R, ImaGL::CImaGL::EPixelType::UByte, 1, 32, 32, "basn0g08.png");
}

TEST_CASE("Opening a 16 bits Gray PNG file", "[basn0g16]")
{
  test_reading<unsigned short>(ImaGL::CImaGL::EPixelFormat::R, ImaGL::CImaGL::EPixelType::UShort, 1, 32, 32, "basn0g16.png");
}

TEST_CASE("Opening a 8 bits Color PNG file", "[basn2c08]")
{
  test_reading<unsigned char>(ImaGL::CImaGL::EPixelFormat::RGB, ImaGL::CImaGL::EPixelType::UByte, 3, 32, 32, "basn2c08.png");
}

TEST_CASE("Opening a 16 bits Color PNG file", "[basn2c16]")
{
  test_reading<unsigned short>(ImaGL::CImaGL::EPixelFormat::RGB, ImaGL::CImaGL::EPixelType::UShort, 3, 32, 32, "basn2c16.png");
}

TEST_CASE("Opening a 1 bit Paletted PNG file", "[basn3p01]")
{
  test_reading<unsigned char>(ImaGL::CImaGL::EPixelFormat::RGB, ImaGL::CImaGL::EPixelType::UByte, 3, 32, 32, "basn3p01.png");
}

TEST_CASE("Opening a 4 bits Paletted PNG file", "[basn3p04]")
{
  test_reading<unsigned char>(ImaGL::CImaGL::EPixelFormat::RGB, ImaGL::CImaGL::EPixelType::UByte, 3, 32, 32, "basn3p04.png");
}

TEST_CASE("Opening a 8 bits Paletted PNG file", "[basn3p08]")
{
  test_reading<unsigned char>(ImaGL::CImaGL::EPixelFormat::RGB, ImaGL::CImaGL::EPixelType::UByte, 3, 32, 32, "basn3p08.png");
}

TEST_CASE("Opening a 8 bits Gray + 8 bits Alpha PNG file", "[basn4a08]")
{
  test_reading<unsigned char>(ImaGL::CImaGL::EPixelFormat::RG, ImaGL::CImaGL::EPixelType::UByte, 2, 32, 32, "basn4a08.png");
}

TEST_CASE("Opening a 16 bits Gray + 16 bits Alpha PNG file", "[basn4a16]")
{
  test_reading<unsigned short>(ImaGL::CImaGL::EPixelFormat::RG, ImaGL::CImaGL::EPixelType::UShort, 2, 32, 32, "basn4a16.png");
}

TEST_CASE("Opening a 8 bits Color + 8 bits Alpha PNG file", "[basn6a08]")
{
  test_reading<unsigned char>(ImaGL::CImaGL::EPixelFormat::RGBA, ImaGL::CImaGL::EPixelType::UByte, 4, 32, 32, "basn6a08.png");
}

TEST_CASE("Opening a 16 bits Color + 16 bits Alpha PNG file", "[basn6a16]")
{
  test_reading<unsigned short>(ImaGL::CImaGL::EPixelFormat::RGBA, ImaGL::CImaGL::EPixelType::UShort, 4, 32, 32, "basn6a16.png");
}



//zlib compressed cases
TEST_CASE("Opening a 8 bits Color PNG file with compression level 0", "[z00n2c08]")
{
  test_reading<unsigned char>(ImaGL::CImaGL::EPixelFormat::RGB, ImaGL::CImaGL::EPixelType::UByte, 3, 32, 32, "z00n2c08.png");
}

TEST_CASE("Opening a 8 bits Color PNG file with compression level 3", "[z03n2c08]")
{
  test_reading<unsigned char>(ImaGL::CImaGL::EPixelFormat::RGB, ImaGL::CImaGL::EPixelType::UByte, 3, 32, 32, "z03n2c08.png");
}

TEST_CASE("Opening a 8 bits Color PNG file with compression level 6", "[z06n2c08]")
{
  test_reading<unsigned char>(ImaGL::CImaGL::EPixelFormat::RGB, ImaGL::CImaGL::EPixelType::UByte, 3, 32, 32, "z06n2c08.png");
}

TEST_CASE("Opening a 8 bits Color PNG file with compression level 9", "[z09n2c08]")
{
  test_reading<unsigned char>(ImaGL::CImaGL::EPixelFormat::RGB, ImaGL::CImaGL::EPixelType::UByte, 3, 32, 32, "z09n2c08.png");
}



//Non square case
TEST_CASE("Opening a 16 bits Color + 16 bits Alpha non squared PNG file ", "[test-16b]")
{
  test_reading<unsigned short>(ImaGL::CImaGL::EPixelFormat::RGBA, ImaGL::CImaGL::EPixelType::UShort, 4, 200, 100, "test-16b.png");
}



//Pixel casts 
TEST_CASE("Pixel casts for reading", "[pixelcast-reading]")
{
  for (size_t test = 0; test < 10; ++test)
  {
    constexpr size_t nRawSize = 32; //The max pixel size is 16 bytes for RGBA / INT configuration. With 32, we can at least access 2 consecutive pixels.
    unsigned char rawData[nRawSize];
    unsigned char rawData_original[nRawSize];
    std::ostringstream ss;
    for (size_t i = 0; i < nRawSize; ++i)
    {
      rawData_original[i] = rawData[i] = (unsigned char)rand();
      ss << "0x" << std::hex << (int)rawData[i] << ", ";
    }
    INFO("Testing with rawData = { " + ss.str().substr(0, ss.str().length() - 2) + " }");

    test_readingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::R, ImaGL::CImaGL::EPixelType::Byte>>(rawData);
    test_readingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::RG, ImaGL::CImaGL::EPixelType::Byte>>(rawData);
    test_readingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::RGB, ImaGL::CImaGL::EPixelType::Byte>>(rawData);
    test_readingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::BGR, ImaGL::CImaGL::EPixelType::Byte>>(rawData);
    test_readingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::RGBA, ImaGL::CImaGL::EPixelType::Byte>>(rawData);
    test_readingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::BGRA, ImaGL::CImaGL::EPixelType::Byte>>(rawData);

    test_readingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::R, ImaGL::CImaGL::EPixelType::Float>>(rawData);
    test_readingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::RG, ImaGL::CImaGL::EPixelType::Float>>(rawData);
    test_readingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::RGB, ImaGL::CImaGL::EPixelType::Float>>(rawData);
    test_readingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::BGR, ImaGL::CImaGL::EPixelType::Float>>(rawData);
    test_readingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::RGBA, ImaGL::CImaGL::EPixelType::Float>>(rawData);
    test_readingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::BGRA, ImaGL::CImaGL::EPixelType::Float>>(rawData);

    //Not supported yet. Need to add an external library to support half float (16bits float)
    //http://half.sourceforge.net could be a solution
    /*test_readingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::R,     ImaGL::CImaGL::EPixelType::HFloat>>(rawData);
    test_readingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::RG,    ImaGL::CImaGL::EPixelType::HFloat>>(rawData);
    test_readingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::RGB,   ImaGL::CImaGL::EPixelType::HFloat>>(rawData);
    test_readingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::BGR,   ImaGL::CImaGL::EPixelType::HFloat>>(rawData);
    test_readingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::RGBA,  ImaGL::CImaGL::EPixelType::HFloat>>(rawData);
    test_readingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::BGRA,  ImaGL::CImaGL::EPixelType::HFloat>>(rawData);*/

    test_readingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::R, ImaGL::CImaGL::EPixelType::Int>>(rawData);
    test_readingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::RG, ImaGL::CImaGL::EPixelType::Int>>(rawData);
    test_readingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::RGB, ImaGL::CImaGL::EPixelType::Int>>(rawData);
    test_readingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::BGR, ImaGL::CImaGL::EPixelType::Int>>(rawData);
    test_readingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::RGBA, ImaGL::CImaGL::EPixelType::Int>>(rawData);
    test_readingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::BGRA, ImaGL::CImaGL::EPixelType::Int>>(rawData);

    test_readingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::R, ImaGL::CImaGL::EPixelType::Short>>(rawData);
    test_readingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::RG, ImaGL::CImaGL::EPixelType::Short>>(rawData);
    test_readingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::RGB, ImaGL::CImaGL::EPixelType::Short>>(rawData);
    test_readingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::BGR, ImaGL::CImaGL::EPixelType::Short>>(rawData);
    test_readingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::RGBA, ImaGL::CImaGL::EPixelType::Short>>(rawData);
    test_readingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::BGRA, ImaGL::CImaGL::EPixelType::Short>>(rawData);

    test_readingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::R, ImaGL::CImaGL::EPixelType::UByte>>(rawData);
    test_readingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::RG, ImaGL::CImaGL::EPixelType::UByte>>(rawData);
    test_readingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::RGB, ImaGL::CImaGL::EPixelType::UByte>>(rawData);
    test_readingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::BGR, ImaGL::CImaGL::EPixelType::UByte>>(rawData);
    test_readingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::RGBA, ImaGL::CImaGL::EPixelType::UByte>>(rawData);
    test_readingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::BGRA, ImaGL::CImaGL::EPixelType::UByte>>(rawData);

    test_readingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::R, ImaGL::CImaGL::EPixelType::UInt>>(rawData);
    test_readingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::RG, ImaGL::CImaGL::EPixelType::UInt>>(rawData);
    test_readingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::RGB, ImaGL::CImaGL::EPixelType::UInt>>(rawData);
    test_readingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::BGR, ImaGL::CImaGL::EPixelType::UInt>>(rawData);
    test_readingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::RGBA, ImaGL::CImaGL::EPixelType::UInt>>(rawData);
    test_readingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::BGRA, ImaGL::CImaGL::EPixelType::UInt>>(rawData);

    test_readingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::R, ImaGL::CImaGL::EPixelType::UShort>>(rawData);
    test_readingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::RG, ImaGL::CImaGL::EPixelType::UShort>>(rawData);
    test_readingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::RGB, ImaGL::CImaGL::EPixelType::UShort>>(rawData);
    test_readingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::BGR, ImaGL::CImaGL::EPixelType::UShort>>(rawData);
    test_readingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::RGBA, ImaGL::CImaGL::EPixelType::UShort>>(rawData);
    test_readingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::BGRA, ImaGL::CImaGL::EPixelType::UShort>>(rawData);

    test_readingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::RGB, ImaGL::CImaGL::EPixelType::UByte_3_3_2>>(rawData);
    test_readingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::BGR, ImaGL::CImaGL::EPixelType::UByte_3_3_2>>(rawData);

    test_readingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::RGB, ImaGL::CImaGL::EPixelType::UByte_2_3_3_Rev>>(rawData);
    test_readingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::BGR, ImaGL::CImaGL::EPixelType::UByte_2_3_3_Rev>>(rawData);

    test_readingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::RGB, ImaGL::CImaGL::EPixelType::UShort_5_6_5>>(rawData);
    test_readingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::BGR, ImaGL::CImaGL::EPixelType::UShort_5_6_5>>(rawData);

    test_readingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::RGB, ImaGL::CImaGL::EPixelType::UShort_5_6_5_Rev>>(rawData);
    test_readingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::BGR, ImaGL::CImaGL::EPixelType::UShort_5_6_5_Rev>>(rawData);

    test_readingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::RGBA, ImaGL::CImaGL::EPixelType::UShort_4_4_4_4>>(rawData);
    test_readingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::BGRA, ImaGL::CImaGL::EPixelType::UShort_4_4_4_4>>(rawData);

    test_readingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::RGBA, ImaGL::CImaGL::EPixelType::UShort_4_4_4_4_Rev>>(rawData);
    test_readingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::BGRA, ImaGL::CImaGL::EPixelType::UShort_4_4_4_4_Rev>>(rawData);

    test_readingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::RGBA, ImaGL::CImaGL::EPixelType::UShort_5_5_5_1>>(rawData);
    test_readingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::BGRA, ImaGL::CImaGL::EPixelType::UShort_5_5_5_1>>(rawData);

    test_readingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::RGBA, ImaGL::CImaGL::EPixelType::UShort_1_5_5_5_Rev>>(rawData);
    test_readingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::BGRA, ImaGL::CImaGL::EPixelType::UShort_1_5_5_5_Rev>>(rawData);

    test_readingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::RGBA, ImaGL::CImaGL::EPixelType::UInt_10_10_10_2>>(rawData);
    test_readingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::BGRA, ImaGL::CImaGL::EPixelType::UInt_10_10_10_2>>(rawData);

    test_readingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::RGBA, ImaGL::CImaGL::EPixelType::UInt_2_10_10_10_Rev>>(rawData);
    test_readingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::BGRA, ImaGL::CImaGL::EPixelType::UInt_2_10_10_10_Rev>>(rawData);

    test_readingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::RGBA, ImaGL::CImaGL::EPixelType::UInt_8_8_8_8>>(rawData);
    test_readingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::BGRA, ImaGL::CImaGL::EPixelType::UInt_8_8_8_8>>(rawData);

    test_readingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::RGBA, ImaGL::CImaGL::EPixelType::UInt_8_8_8_8_Rev>>(rawData);
    test_readingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::BGRA, ImaGL::CImaGL::EPixelType::UInt_8_8_8_8_Rev>>(rawData);


    //Ensure that no data corruption happened during reading operations
    size_t i = 0;
    unsigned char* p1 = rawData_original;
    unsigned char* p2 = rawData;
    for (i = 0; i < nRawSize; ++i, ++p1, ++p2)
    {
      if (*p1 != *p2)
      {
        break;
      }
    }
    CHECK(i == nRawSize);
  }
}

TEST_CASE("Pixel casts for writing", "[pixelcast-writing]")
{
  for (size_t test = 0; test < 10; ++test)
  {
    test_writingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::R, ImaGL::CImaGL::EPixelType::Byte>>();
    test_writingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::RG, ImaGL::CImaGL::EPixelType::Byte>>();
    test_writingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::RGB, ImaGL::CImaGL::EPixelType::Byte>>();
    test_writingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::BGR, ImaGL::CImaGL::EPixelType::Byte>>();
    test_writingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::RGBA, ImaGL::CImaGL::EPixelType::Byte>>();
    test_writingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::BGRA, ImaGL::CImaGL::EPixelType::Byte>>();

    test_writingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::R, ImaGL::CImaGL::EPixelType::Float>>();
    test_writingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::RG, ImaGL::CImaGL::EPixelType::Float>>();
    test_writingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::RGB, ImaGL::CImaGL::EPixelType::Float>>();
    test_writingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::BGR, ImaGL::CImaGL::EPixelType::Float>>();
    test_writingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::RGBA, ImaGL::CImaGL::EPixelType::Float>>();
    test_writingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::BGRA, ImaGL::CImaGL::EPixelType::Float>>();

    //Not supported yet. Need to add an external library to support half float (16bits float)
    //http://half.sourceforge.net could be a solution
    /*test_writingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::R,     ImaGL::CImaGL::EPixelType::HFloat>>();
    test_writingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::RG,    ImaGL::CImaGL::EPixelType::HFloat>>();
    test_writingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::RGB,   ImaGL::CImaGL::EPixelType::HFloat>>();
    test_writingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::BGR,   ImaGL::CImaGL::EPixelType::HFloat>>();
    test_writingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::RGBA,  ImaGL::CImaGL::EPixelType::HFloat>>();
    test_writingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::BGRA,  ImaGL::CImaGL::EPixelType::HFloat>>();*/

    test_writingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::R, ImaGL::CImaGL::EPixelType::Int>>();
    test_writingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::RG, ImaGL::CImaGL::EPixelType::Int>>();
    test_writingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::RGB, ImaGL::CImaGL::EPixelType::Int>>();
    test_writingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::BGR, ImaGL::CImaGL::EPixelType::Int>>();
    test_writingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::RGBA, ImaGL::CImaGL::EPixelType::Int>>();
    test_writingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::BGRA, ImaGL::CImaGL::EPixelType::Int>>();

    test_writingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::R, ImaGL::CImaGL::EPixelType::Short>>();
    test_writingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::RG, ImaGL::CImaGL::EPixelType::Short>>();
    test_writingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::RGB, ImaGL::CImaGL::EPixelType::Short>>();
    test_writingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::BGR, ImaGL::CImaGL::EPixelType::Short>>();
    test_writingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::RGBA, ImaGL::CImaGL::EPixelType::Short>>();
    test_writingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::BGRA, ImaGL::CImaGL::EPixelType::Short>>();

    test_writingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::R, ImaGL::CImaGL::EPixelType::UByte>>();
    test_writingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::RG, ImaGL::CImaGL::EPixelType::UByte>>();
    test_writingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::RGB, ImaGL::CImaGL::EPixelType::UByte>>();
    test_writingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::BGR, ImaGL::CImaGL::EPixelType::UByte>>();
    test_writingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::RGBA, ImaGL::CImaGL::EPixelType::UByte>>();
    test_writingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::BGRA, ImaGL::CImaGL::EPixelType::UByte>>();

    test_writingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::R, ImaGL::CImaGL::EPixelType::UInt>>();
    test_writingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::RG, ImaGL::CImaGL::EPixelType::UInt>>();
    test_writingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::RGB, ImaGL::CImaGL::EPixelType::UInt>>();
    test_writingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::BGR, ImaGL::CImaGL::EPixelType::UInt>>();
    test_writingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::RGBA, ImaGL::CImaGL::EPixelType::UInt>>();
    test_writingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::BGRA, ImaGL::CImaGL::EPixelType::UInt>>();

    test_writingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::R, ImaGL::CImaGL::EPixelType::UShort>>();
    test_writingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::RG, ImaGL::CImaGL::EPixelType::UShort>>();
    test_writingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::RGB, ImaGL::CImaGL::EPixelType::UShort>>();
    test_writingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::BGR, ImaGL::CImaGL::EPixelType::UShort>>();
    test_writingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::RGBA, ImaGL::CImaGL::EPixelType::UShort>>();
    test_writingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::BGRA, ImaGL::CImaGL::EPixelType::UShort>>();

    test_writingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::RGB, ImaGL::CImaGL::EPixelType::UByte_3_3_2>>();
    test_writingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::BGR, ImaGL::CImaGL::EPixelType::UByte_3_3_2>>();

    test_writingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::RGB, ImaGL::CImaGL::EPixelType::UByte_2_3_3_Rev>>();
    test_writingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::BGR, ImaGL::CImaGL::EPixelType::UByte_2_3_3_Rev>>();

    test_writingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::RGB, ImaGL::CImaGL::EPixelType::UShort_5_6_5>>();
    test_writingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::BGR, ImaGL::CImaGL::EPixelType::UShort_5_6_5>>();

    test_writingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::RGB, ImaGL::CImaGL::EPixelType::UShort_5_6_5_Rev>>();
    test_writingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::BGR, ImaGL::CImaGL::EPixelType::UShort_5_6_5_Rev>>();

    test_writingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::RGBA, ImaGL::CImaGL::EPixelType::UShort_4_4_4_4>>();
    test_writingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::BGRA, ImaGL::CImaGL::EPixelType::UShort_4_4_4_4>>();

    test_writingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::RGBA, ImaGL::CImaGL::EPixelType::UShort_4_4_4_4_Rev>>();
    test_writingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::BGRA, ImaGL::CImaGL::EPixelType::UShort_4_4_4_4_Rev>>();

    test_writingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::RGBA, ImaGL::CImaGL::EPixelType::UShort_5_5_5_1>>();
    test_writingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::BGRA, ImaGL::CImaGL::EPixelType::UShort_5_5_5_1>>();

    test_writingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::RGBA, ImaGL::CImaGL::EPixelType::UShort_1_5_5_5_Rev>>();
    test_writingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::BGRA, ImaGL::CImaGL::EPixelType::UShort_1_5_5_5_Rev>>();

    test_writingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::RGBA, ImaGL::CImaGL::EPixelType::UInt_10_10_10_2>>();
    test_writingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::BGRA, ImaGL::CImaGL::EPixelType::UInt_10_10_10_2>>();

    test_writingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::RGBA, ImaGL::CImaGL::EPixelType::UInt_2_10_10_10_Rev>>();
    test_writingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::BGRA, ImaGL::CImaGL::EPixelType::UInt_2_10_10_10_Rev>>();

    test_writingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::RGBA, ImaGL::CImaGL::EPixelType::UInt_8_8_8_8>>();
    test_writingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::BGRA, ImaGL::CImaGL::EPixelType::UInt_8_8_8_8>>();

    test_writingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::RGBA, ImaGL::CImaGL::EPixelType::UInt_8_8_8_8_Rev>>();
    test_writingPixels<ImaGL::Pixel<ImaGL::CImaGL::EPixelFormat::BGRA, ImaGL::CImaGL::EPixelType::UInt_8_8_8_8_Rev>>();

  }
}


TEST_CASE("Downscaling image", "[downscaling]")
{
#define resize_img_to(width, height) \
  ImaGL::CImaGL img_##width##_##height(img);\
  img_##width##_##height.rescale(width, height);\
  export_FITS_file(img_##width##_##height, "downscaling_"#width"_"#height".fit")

  ImaGL::CImaGL img("test-16b.png");

  resize_img_to(128, 100);
  resize_img_to(32, 100);
  resize_img_to(35, 100);

  resize_img_to(200, 64);
  resize_img_to(200, 32);
  resize_img_to(200, 35);

  resize_img_to(40, 20);

#undef resize_img_to
}