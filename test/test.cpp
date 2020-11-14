// test.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//
#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() 

#include "test.h"
#include <sstream>

//interlaced cases
TEST_CASE("Opening a 1 bit Gray interlaced PNG file", "[basi0g01]")
{
  test_reading<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::R, imaGL::CImaGL::EPixelType::UByte>>(32, 32, imaGL::CImaGL("basi0g01.png"), "basi0g01.png");
}

TEST_CASE("Opening a 2 bits Gray interlaced PNG file", "[basi0g02]")
{
  test_reading<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::R, imaGL::CImaGL::EPixelType::UByte>>(32, 32, imaGL::CImaGL("basi0g02.png"), "basi0g02.png");
}

TEST_CASE("Opening a 4 bits Gray interlaced PNG file", "[basi0g04]")
{
  test_reading<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::R, imaGL::CImaGL::EPixelType::UByte>>(32, 32, imaGL::CImaGL("basi0g04.png"), "basi0g04.png");
}

TEST_CASE("Opening a 8 bits Gray interlaced PNG file", "[basi0g08]")
{
  test_reading<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::R, imaGL::CImaGL::EPixelType::UByte>>(32, 32, imaGL::CImaGL("basi0g08.png"), "basi0g08.png");
}

TEST_CASE("Opening a 16 bits Gray interlaced PNG file", "[basi0g16]")
{
  test_reading<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::R, imaGL::CImaGL::EPixelType::UShort>>(32, 32, imaGL::CImaGL("basi0g16.png"), "basi0g16.png");
}

TEST_CASE("Opening a 8 bits Color interlaced PNG file", "[basi2c08]")
{
  test_reading<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGB, imaGL::CImaGL::EPixelType::UByte>>(32, 32, imaGL::CImaGL("basi2c08.png"), "basi2c08.png");
}

TEST_CASE("Opening a 16 bits Color interlaced PNG file", "[basi2c16]")
{
  test_reading<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGB, imaGL::CImaGL::EPixelType::UShort>>(32, 32, imaGL::CImaGL("basi2c16.png"), "basi2c16.png");
}

TEST_CASE("Opening a 1 bit Paletted interlaced PNG file", "[basi3p01]")
{
  test_reading<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGB, imaGL::CImaGL::EPixelType::UByte>>(32, 32, imaGL::CImaGL("basi3p01.png"), "basi3p01.png");
}

TEST_CASE("Opening a 4 bits Paletted interlaced PNG file", "[basi3p04]")
{
  test_reading<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGB, imaGL::CImaGL::EPixelType::UByte>>(32, 32, imaGL::CImaGL("basi3p04.png"), "basi3p04.png");
}

TEST_CASE("Opening a 8 bits Paletted interlaced PNG file", "[basi3p08]")
{
  test_reading<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGB, imaGL::CImaGL::EPixelType::UByte>>(32, 32, imaGL::CImaGL("basi3p08.png"), "basi3p08.png");
}

TEST_CASE("Opening a 8 bits Gray + 8 bits Alpha interlaced PNG file", "[basi4a08]")
{
  test_reading<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RG, imaGL::CImaGL::EPixelType::UByte>>(32, 32, imaGL::CImaGL("basi4a08.png"), "basi4a08.png");
}

TEST_CASE("Opening a 16 bits Gray + 16 bits Alpha interlaced PNG file", "[basi4a16]")
{
  test_reading<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RG, imaGL::CImaGL::EPixelType::UShort>>(32, 32, imaGL::CImaGL("basi4a16.png"), "basi4a16.png");
}

TEST_CASE("Opening a 8 bits Color + 8 bits Alpha interlaced PNG file", "[basi6a08]")
{
  test_reading<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGBA, imaGL::CImaGL::EPixelType::UByte>>(32, 32, imaGL::CImaGL("basi6a08.png"), "basi6a08.png");
}

TEST_CASE("Opening a 16 bits Color + 16 bits Alpha interlaced PNG file", "[basi6a16]")
{
  test_reading<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGBA, imaGL::CImaGL::EPixelType::UShort>>(32, 32, imaGL::CImaGL("basi6a16.png"), "basi6a16.png");
}



//non interlaced cases
TEST_CASE("Opening a 1 bit Gray PNG file", "[basn0g01]")
{
  test_reading<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::R, imaGL::CImaGL::EPixelType::UByte>>(32, 32, imaGL::CImaGL("basn0g01.png"), "basn0g01.png");
}

TEST_CASE("Opening a 2 bits Gray PNG file", "[basn0g02]")
{
  test_reading<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::R, imaGL::CImaGL::EPixelType::UByte>>(32, 32, imaGL::CImaGL("basn0g02.png"), "basn0g02.png");
}

TEST_CASE("Opening a 4 bits Gray PNG file", "[basn0g04]")
{
  test_reading<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::R, imaGL::CImaGL::EPixelType::UByte>>(32, 32, imaGL::CImaGL("basn0g04.png"), "basn0g04.png");
}

TEST_CASE("Opening a 8 bits Gray PNG file", "[basn0g08]")
{
  test_reading<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::R, imaGL::CImaGL::EPixelType::UByte>>(32, 32, imaGL::CImaGL("basn0g08.png"), "basn0g08.png");
}

TEST_CASE("Opening a 16 bits Gray PNG file", "[basn0g16]")
{
  test_reading<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::R, imaGL::CImaGL::EPixelType::UShort>>(32, 32, imaGL::CImaGL("basn0g16.png"), "basn0g16.png");
}

TEST_CASE("Opening a 8 bits Color PNG file", "[basn2c08]")
{
  test_reading<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGB, imaGL::CImaGL::EPixelType::UByte>>(32, 32, imaGL::CImaGL("basn2c08.png"), "basn2c08.png");
}

TEST_CASE("Opening a 16 bits Color PNG file", "[basn2c16]")
{
  test_reading<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGB, imaGL::CImaGL::EPixelType::UShort>>(32, 32, imaGL::CImaGL("basn2c16.png"), "basn2c16.png");
}

TEST_CASE("Opening a 1 bit Paletted PNG file", "[basn3p01]")
{
  test_reading<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGB, imaGL::CImaGL::EPixelType::UByte>>(32, 32, imaGL::CImaGL("basn3p01.png"), "basn3p01.png");
}

TEST_CASE("Opening a 4 bits Paletted PNG file", "[basn3p04]")
{
  test_reading<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGB, imaGL::CImaGL::EPixelType::UByte>>(32, 32, imaGL::CImaGL("basn3p04.png"), "basn3p04.png");
}

TEST_CASE("Opening a 8 bits Paletted PNG file", "[basn3p08]")
{
  test_reading<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGB, imaGL::CImaGL::EPixelType::UByte>>(32, 32, imaGL::CImaGL("basn3p08.png"), "basn3p08.png");
}

TEST_CASE("Opening a 8 bits Gray + 8 bits Alpha PNG file", "[basn4a08]")
{
  test_reading<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RG, imaGL::CImaGL::EPixelType::UByte>>(32, 32, imaGL::CImaGL("basn4a08.png"), "basn4a08.png");
}

TEST_CASE("Opening a 16 bits Gray + 16 bits Alpha PNG file", "[basn4a16]")
{
  test_reading<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RG, imaGL::CImaGL::EPixelType::UShort>>(32, 32, imaGL::CImaGL("basn4a16.png"), "basn4a16.png");
}

TEST_CASE("Opening a 8 bits Color + 8 bits Alpha PNG file", "[basn6a08]")
{
  test_reading<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGBA, imaGL::CImaGL::EPixelType::UByte>>(32, 32, imaGL::CImaGL("basn6a08.png"), "basn6a08.png");
}

TEST_CASE("Opening a 16 bits Color + 16 bits Alpha PNG file", "[basn6a16]")
{
  test_reading<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGBA, imaGL::CImaGL::EPixelType::UShort>>(32, 32, imaGL::CImaGL("basn6a16.png"), "basn6a16.png");
}



//zlib compressed cases
TEST_CASE("Opening a 8 bits Color PNG file with compression level 0", "[z00n2c08]")
{
  test_reading<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGB, imaGL::CImaGL::EPixelType::UByte>>(32, 32, imaGL::CImaGL("z00n2c08.png"), "z00n2c08.png");
}

TEST_CASE("Opening a 8 bits Color PNG file with compression level 3", "[z03n2c08]")
{
  test_reading<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGB, imaGL::CImaGL::EPixelType::UByte>>(32, 32, imaGL::CImaGL("z03n2c08.png"), "z03n2c08.png");
}

TEST_CASE("Opening a 8 bits Color PNG file with compression level 6", "[z06n2c08]")
{
  test_reading<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGB, imaGL::CImaGL::EPixelType::UByte>>(32, 32, imaGL::CImaGL("z06n2c08.png"), "z06n2c08.png");
}

TEST_CASE("Opening a 8 bits Color PNG file with compression level 9", "[z09n2c08]")
{
  test_reading<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGB, imaGL::CImaGL::EPixelType::UByte>>(32, 32, imaGL::CImaGL("z09n2c08.png"), "z09n2c08.png");
}



//Non square case
TEST_CASE("Opening a 16 bits Color + 16 bits Alpha non squared PNG file ", "[test-16b]")
{
  test_reading<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGBA, imaGL::CImaGL::EPixelType::UShort>>(200, 100, imaGL::CImaGL("test-16b.png"), "test-16b.png");
}



//Pixel casts 
TEST_CASE("Pixel casts for reading", "[pixelcast-reading]")
{
  for (size_t test = 0; test < 10; ++test)
  {
    constexpr size_t nRawSize = 32; //The max pixel size is 16 bytes for RGBA / INT configuration. With 32, we can at least access 2 consecutive pixels.
    std::byte rawData[nRawSize];
    std::byte rawData_original[nRawSize];
    std::ostringstream ss;
    for (size_t i = 0; i < nRawSize; ++i)
    {
      rawData_original[i] = rawData[i] = (std::byte)rand();
      ss << "0x" << std::hex << (int)rawData[i] << ", ";
    }
    INFO("Testing with rawData = { " + ss.str().substr(0, ss.str().length() - 2) + " }");

    test_readingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::R, imaGL::CImaGL::EPixelType::Byte>>(rawData);
    test_readingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RG, imaGL::CImaGL::EPixelType::Byte>>(rawData);
    test_readingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGB, imaGL::CImaGL::EPixelType::Byte>>(rawData);
    test_readingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::BGR, imaGL::CImaGL::EPixelType::Byte>>(rawData);
    test_readingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGBA, imaGL::CImaGL::EPixelType::Byte>>(rawData);
    test_readingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::BGRA, imaGL::CImaGL::EPixelType::Byte>>(rawData);

    test_readingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::R, imaGL::CImaGL::EPixelType::Float>>(rawData);
    test_readingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RG, imaGL::CImaGL::EPixelType::Float>>(rawData);
    test_readingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGB, imaGL::CImaGL::EPixelType::Float>>(rawData);
    test_readingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::BGR, imaGL::CImaGL::EPixelType::Float>>(rawData);
    test_readingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGBA, imaGL::CImaGL::EPixelType::Float>>(rawData);
    test_readingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::BGRA, imaGL::CImaGL::EPixelType::Float>>(rawData);

    //Not supported yet. Need to add an external library to support half float (16bits float)
    //http://half.sourceforge.net could be a solution
    /*test_readingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::R,     imaGL::CImaGL::EPixelType::HFloat>>(rawData);
    test_readingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RG,    imaGL::CImaGL::EPixelType::HFloat>>(rawData);
    test_readingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGB,   imaGL::CImaGL::EPixelType::HFloat>>(rawData);
    test_readingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::BGR,   imaGL::CImaGL::EPixelType::HFloat>>(rawData);
    test_readingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGBA,  imaGL::CImaGL::EPixelType::HFloat>>(rawData);
    test_readingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::BGRA,  imaGL::CImaGL::EPixelType::HFloat>>(rawData);*/

    test_readingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::R, imaGL::CImaGL::EPixelType::Int>>(rawData);
    test_readingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RG, imaGL::CImaGL::EPixelType::Int>>(rawData);
    test_readingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGB, imaGL::CImaGL::EPixelType::Int>>(rawData);
    test_readingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::BGR, imaGL::CImaGL::EPixelType::Int>>(rawData);
    test_readingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGBA, imaGL::CImaGL::EPixelType::Int>>(rawData);
    test_readingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::BGRA, imaGL::CImaGL::EPixelType::Int>>(rawData);

    test_readingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::R, imaGL::CImaGL::EPixelType::Short>>(rawData);
    test_readingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RG, imaGL::CImaGL::EPixelType::Short>>(rawData);
    test_readingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGB, imaGL::CImaGL::EPixelType::Short>>(rawData);
    test_readingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::BGR, imaGL::CImaGL::EPixelType::Short>>(rawData);
    test_readingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGBA, imaGL::CImaGL::EPixelType::Short>>(rawData);
    test_readingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::BGRA, imaGL::CImaGL::EPixelType::Short>>(rawData);

    test_readingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::R, imaGL::CImaGL::EPixelType::UByte>>(rawData);
    test_readingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RG, imaGL::CImaGL::EPixelType::UByte>>(rawData);
    test_readingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGB, imaGL::CImaGL::EPixelType::UByte>>(rawData);
    test_readingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::BGR, imaGL::CImaGL::EPixelType::UByte>>(rawData);
    test_readingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGBA, imaGL::CImaGL::EPixelType::UByte>>(rawData);
    test_readingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::BGRA, imaGL::CImaGL::EPixelType::UByte>>(rawData);

    test_readingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::R, imaGL::CImaGL::EPixelType::UInt>>(rawData);
    test_readingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RG, imaGL::CImaGL::EPixelType::UInt>>(rawData);
    test_readingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGB, imaGL::CImaGL::EPixelType::UInt>>(rawData);
    test_readingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::BGR, imaGL::CImaGL::EPixelType::UInt>>(rawData);
    test_readingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGBA, imaGL::CImaGL::EPixelType::UInt>>(rawData);
    test_readingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::BGRA, imaGL::CImaGL::EPixelType::UInt>>(rawData);

    test_readingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::R, imaGL::CImaGL::EPixelType::UShort>>(rawData);
    test_readingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RG, imaGL::CImaGL::EPixelType::UShort>>(rawData);
    test_readingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGB, imaGL::CImaGL::EPixelType::UShort>>(rawData);
    test_readingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::BGR, imaGL::CImaGL::EPixelType::UShort>>(rawData);
    test_readingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGBA, imaGL::CImaGL::EPixelType::UShort>>(rawData);
    test_readingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::BGRA, imaGL::CImaGL::EPixelType::UShort>>(rawData);

    test_readingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGB, imaGL::CImaGL::EPixelType::UByte_3_3_2>>(rawData);
    test_readingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::BGR, imaGL::CImaGL::EPixelType::UByte_3_3_2>>(rawData);

    test_readingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGB, imaGL::CImaGL::EPixelType::UByte_2_3_3_Rev>>(rawData);
    test_readingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::BGR, imaGL::CImaGL::EPixelType::UByte_2_3_3_Rev>>(rawData);

    test_readingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGB, imaGL::CImaGL::EPixelType::UShort_5_6_5>>(rawData);
    test_readingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::BGR, imaGL::CImaGL::EPixelType::UShort_5_6_5>>(rawData);

    test_readingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGB, imaGL::CImaGL::EPixelType::UShort_5_6_5_Rev>>(rawData);
    test_readingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::BGR, imaGL::CImaGL::EPixelType::UShort_5_6_5_Rev>>(rawData);

    test_readingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGBA, imaGL::CImaGL::EPixelType::UShort_4_4_4_4>>(rawData);
    test_readingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::BGRA, imaGL::CImaGL::EPixelType::UShort_4_4_4_4>>(rawData);

    test_readingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGBA, imaGL::CImaGL::EPixelType::UShort_4_4_4_4_Rev>>(rawData);
    test_readingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::BGRA, imaGL::CImaGL::EPixelType::UShort_4_4_4_4_Rev>>(rawData);

    test_readingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGBA, imaGL::CImaGL::EPixelType::UShort_5_5_5_1>>(rawData);
    test_readingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::BGRA, imaGL::CImaGL::EPixelType::UShort_5_5_5_1>>(rawData);

    test_readingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGBA, imaGL::CImaGL::EPixelType::UShort_1_5_5_5_Rev>>(rawData);
    test_readingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::BGRA, imaGL::CImaGL::EPixelType::UShort_1_5_5_5_Rev>>(rawData);

    test_readingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGBA, imaGL::CImaGL::EPixelType::UInt_10_10_10_2>>(rawData);
    test_readingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::BGRA, imaGL::CImaGL::EPixelType::UInt_10_10_10_2>>(rawData);

    test_readingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGBA, imaGL::CImaGL::EPixelType::UInt_2_10_10_10_Rev>>(rawData);
    test_readingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::BGRA, imaGL::CImaGL::EPixelType::UInt_2_10_10_10_Rev>>(rawData);

    test_readingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGBA, imaGL::CImaGL::EPixelType::UInt_8_8_8_8>>(rawData);
    test_readingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::BGRA, imaGL::CImaGL::EPixelType::UInt_8_8_8_8>>(rawData);

    test_readingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGBA, imaGL::CImaGL::EPixelType::UInt_8_8_8_8_Rev>>(rawData);
    test_readingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::BGRA, imaGL::CImaGL::EPixelType::UInt_8_8_8_8_Rev>>(rawData);


    //Ensure that no data corruption happened during reading operations
    size_t i = 0;
    std::byte* p1 = rawData_original;
    std::byte* p2 = rawData;
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
    test_writingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::R, imaGL::CImaGL::EPixelType::Byte>>();
    test_writingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RG, imaGL::CImaGL::EPixelType::Byte>>();
    test_writingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGB, imaGL::CImaGL::EPixelType::Byte>>();
    test_writingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::BGR, imaGL::CImaGL::EPixelType::Byte>>();
    test_writingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGBA, imaGL::CImaGL::EPixelType::Byte>>();
    test_writingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::BGRA, imaGL::CImaGL::EPixelType::Byte>>();

    test_writingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::R, imaGL::CImaGL::EPixelType::Float>>();
    test_writingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RG, imaGL::CImaGL::EPixelType::Float>>();
    test_writingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGB, imaGL::CImaGL::EPixelType::Float>>();
    test_writingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::BGR, imaGL::CImaGL::EPixelType::Float>>();
    test_writingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGBA, imaGL::CImaGL::EPixelType::Float>>();
    test_writingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::BGRA, imaGL::CImaGL::EPixelType::Float>>();

    //Not supported yet. Need to add an external library to support half float (16bits float)
    //http://half.sourceforge.net could be a solution
    /*test_writingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::R,     imaGL::CImaGL::EPixelType::HFloat>>();
    test_writingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RG,    imaGL::CImaGL::EPixelType::HFloat>>();
    test_writingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGB,   imaGL::CImaGL::EPixelType::HFloat>>();
    test_writingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::BGR,   imaGL::CImaGL::EPixelType::HFloat>>();
    test_writingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGBA,  imaGL::CImaGL::EPixelType::HFloat>>();
    test_writingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::BGRA,  imaGL::CImaGL::EPixelType::HFloat>>();*/

    test_writingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::R, imaGL::CImaGL::EPixelType::Int>>();
    test_writingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RG, imaGL::CImaGL::EPixelType::Int>>();
    test_writingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGB, imaGL::CImaGL::EPixelType::Int>>();
    test_writingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::BGR, imaGL::CImaGL::EPixelType::Int>>();
    test_writingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGBA, imaGL::CImaGL::EPixelType::Int>>();
    test_writingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::BGRA, imaGL::CImaGL::EPixelType::Int>>();

    test_writingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::R, imaGL::CImaGL::EPixelType::Short>>();
    test_writingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RG, imaGL::CImaGL::EPixelType::Short>>();
    test_writingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGB, imaGL::CImaGL::EPixelType::Short>>();
    test_writingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::BGR, imaGL::CImaGL::EPixelType::Short>>();
    test_writingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGBA, imaGL::CImaGL::EPixelType::Short>>();
    test_writingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::BGRA, imaGL::CImaGL::EPixelType::Short>>();

    test_writingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::R, imaGL::CImaGL::EPixelType::UByte>>();
    test_writingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RG, imaGL::CImaGL::EPixelType::UByte>>();
    test_writingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGB, imaGL::CImaGL::EPixelType::UByte>>();
    test_writingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::BGR, imaGL::CImaGL::EPixelType::UByte>>();
    test_writingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGBA, imaGL::CImaGL::EPixelType::UByte>>();
    test_writingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::BGRA, imaGL::CImaGL::EPixelType::UByte>>();

    test_writingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::R, imaGL::CImaGL::EPixelType::UInt>>();
    test_writingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RG, imaGL::CImaGL::EPixelType::UInt>>();
    test_writingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGB, imaGL::CImaGL::EPixelType::UInt>>();
    test_writingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::BGR, imaGL::CImaGL::EPixelType::UInt>>();
    test_writingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGBA, imaGL::CImaGL::EPixelType::UInt>>();
    test_writingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::BGRA, imaGL::CImaGL::EPixelType::UInt>>();

    test_writingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::R, imaGL::CImaGL::EPixelType::UShort>>();
    test_writingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RG, imaGL::CImaGL::EPixelType::UShort>>();
    test_writingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGB, imaGL::CImaGL::EPixelType::UShort>>();
    test_writingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::BGR, imaGL::CImaGL::EPixelType::UShort>>();
    test_writingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGBA, imaGL::CImaGL::EPixelType::UShort>>();
    test_writingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::BGRA, imaGL::CImaGL::EPixelType::UShort>>();

    test_writingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGB, imaGL::CImaGL::EPixelType::UByte_3_3_2>>();
    test_writingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::BGR, imaGL::CImaGL::EPixelType::UByte_3_3_2>>();

    test_writingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGB, imaGL::CImaGL::EPixelType::UByte_2_3_3_Rev>>();
    test_writingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::BGR, imaGL::CImaGL::EPixelType::UByte_2_3_3_Rev>>();

    test_writingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGB, imaGL::CImaGL::EPixelType::UShort_5_6_5>>();
    test_writingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::BGR, imaGL::CImaGL::EPixelType::UShort_5_6_5>>();

    test_writingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGB, imaGL::CImaGL::EPixelType::UShort_5_6_5_Rev>>();
    test_writingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::BGR, imaGL::CImaGL::EPixelType::UShort_5_6_5_Rev>>();

    test_writingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGBA, imaGL::CImaGL::EPixelType::UShort_4_4_4_4>>();
    test_writingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::BGRA, imaGL::CImaGL::EPixelType::UShort_4_4_4_4>>();

    test_writingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGBA, imaGL::CImaGL::EPixelType::UShort_4_4_4_4_Rev>>();
    test_writingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::BGRA, imaGL::CImaGL::EPixelType::UShort_4_4_4_4_Rev>>();

    test_writingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGBA, imaGL::CImaGL::EPixelType::UShort_5_5_5_1>>();
    test_writingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::BGRA, imaGL::CImaGL::EPixelType::UShort_5_5_5_1>>();

    test_writingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGBA, imaGL::CImaGL::EPixelType::UShort_1_5_5_5_Rev>>();
    test_writingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::BGRA, imaGL::CImaGL::EPixelType::UShort_1_5_5_5_Rev>>();

    test_writingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGBA, imaGL::CImaGL::EPixelType::UInt_10_10_10_2>>();
    test_writingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::BGRA, imaGL::CImaGL::EPixelType::UInt_10_10_10_2>>();

    test_writingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGBA, imaGL::CImaGL::EPixelType::UInt_2_10_10_10_Rev>>();
    test_writingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::BGRA, imaGL::CImaGL::EPixelType::UInt_2_10_10_10_Rev>>();

    test_writingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGBA, imaGL::CImaGL::EPixelType::UInt_8_8_8_8>>();
    test_writingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::BGRA, imaGL::CImaGL::EPixelType::UInt_8_8_8_8>>();

    test_writingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGBA, imaGL::CImaGL::EPixelType::UInt_8_8_8_8_Rev>>();
    test_writingPixels<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::BGRA, imaGL::CImaGL::EPixelType::UInt_8_8_8_8_Rev>>();
  }
}


TEST_CASE("Scaling image", "[scaling]")
{
  std::string strFileName = "test-16b.png";
  imaGL::CImaGL img_16b_rgba(strFileName);

  test_img_rescale<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGBA, imaGL::CImaGL::EPixelType::UShort>>(img_16b_rgba, strFileName, 128, 100);
  test_img_rescale<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGBA, imaGL::CImaGL::EPixelType::UShort>>(img_16b_rgba, strFileName, 32, 100);
  test_img_rescale<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGBA, imaGL::CImaGL::EPixelType::UShort>>(img_16b_rgba, strFileName, 35, 100);

  test_img_rescale<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGBA, imaGL::CImaGL::EPixelType::UShort>>(img_16b_rgba, strFileName, 200, 64);
  test_img_rescale<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGBA, imaGL::CImaGL::EPixelType::UShort>>(img_16b_rgba, strFileName, 200, 32);
  test_img_rescale<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGBA, imaGL::CImaGL::EPixelType::UShort>>(img_16b_rgba, strFileName, 200, 35);

  test_img_rescale<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGBA, imaGL::CImaGL::EPixelType::UShort>>(img_16b_rgba, strFileName, 40, 20);

  test_img_rescale<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGBA, imaGL::CImaGL::EPixelType::UShort>>(img_16b_rgba, strFileName, 400, 200);
  test_img_rescale<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGBA, imaGL::CImaGL::EPixelType::UShort>>(img_16b_rgba, strFileName, 256, 256);

  strFileName = "test-16b-odd.png";
  imaGL::CImaGL img_16b_rgba_odd(strFileName);

  test_img_rescale<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGBA, imaGL::CImaGL::EPixelType::UShort>>(img_16b_rgba_odd, strFileName, 128, 100);
  test_img_rescale<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGBA, imaGL::CImaGL::EPixelType::UShort>>(img_16b_rgba_odd, strFileName, 32, 100);
  test_img_rescale<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGBA, imaGL::CImaGL::EPixelType::UShort>>(img_16b_rgba_odd, strFileName, 35, 100);

  test_img_rescale<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGBA, imaGL::CImaGL::EPixelType::UShort>>(img_16b_rgba_odd, strFileName, 200, 64);
  test_img_rescale<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGBA, imaGL::CImaGL::EPixelType::UShort>>(img_16b_rgba_odd, strFileName, 200, 32);
  test_img_rescale<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGBA, imaGL::CImaGL::EPixelType::UShort>>(img_16b_rgba_odd, strFileName, 200, 35);

  test_img_rescale<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGBA, imaGL::CImaGL::EPixelType::UShort>>(img_16b_rgba_odd, strFileName, 40, 20);

  test_img_rescale<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGBA, imaGL::CImaGL::EPixelType::UShort>>(img_16b_rgba_odd, strFileName, 400, 200);
  test_img_rescale<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGBA, imaGL::CImaGL::EPixelType::UShort>>(img_16b_rgba_odd, strFileName, 256, 256);
}

TEST_CASE("Scaling image (next power of 2)", "[scaling-pow2]")
{
  std::string strFileName = "test-16b.png";
  imaGL::CImaGL img_16b_rgba(strFileName);

  img_16b_rgba.rescaleToNextPowerOfTwo();

  CHECK(img_16b_rgba.width() == 256);
  CHECK(img_16b_rgba.height() == 128);

  img_16b_rgba.rescaleToNextPowerOfTwo();

  CHECK(img_16b_rgba.width() == 256);
  CHECK(img_16b_rgba.height() == 128);
}