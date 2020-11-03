// test.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//
#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() 

#include "test.h"

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
