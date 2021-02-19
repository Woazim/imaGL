#include "test.h"

#ifdef _HAS_PNG

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

TEST_CASE("Opening a PNG file from memory", "[opening-png-from-memory]")
{
  using namespace imaGL::string_literals;

  std::ifstream ifs("test-16b.png", std::ios::in | std::ios::binary);
  REQUIRE(ifs.is_open());

  //Read all content of the file
  ifs.seekg(0, std::ios::end);
  size_t length = ifs.tellg();
  ifs.seekg(0, std::ios::beg);
  std::string buffer(length, '\0');
  ifs.read(buffer.data(), length);

  //Encapsulate raw buffer in a stream buffer
  std::istringstream iss(std::move(buffer), std::ios::in | std::ios::binary);

  //Try to open from a PNG
  imaGL::CImaGL imgPNG(iss, "PNG "_FF);
  test_reading<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGBA, imaGL::CImaGL::EPixelType::UShort>>(200, 100, imgPNG, "test-16b.png");

  //Try to open from an unknown type
  iss.seekg(0, std::ios::beg);
  imaGL::CImaGL imgUnknown(iss);
  test_reading<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGBA, imaGL::CImaGL::EPixelType::UShort>>(200, 100, imgUnknown, "test-16b.png");
}

#endif // _HAS_PNG

