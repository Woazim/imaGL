#include "test.h"

TEST_CASE("Opening a RGB JPEG file", "[rgbjpeg]")
{
  test_reading<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGB, imaGL::CImaGL::EPixelType::UByte>>(200, 100, imaGL::CImaGL("test-rgb.jpg"), "test-rgb.jpg");
}

TEST_CASE("Opening a gray JPEG file", "[grayjpeg]")
{
  test_reading<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::R, imaGL::CImaGL::EPixelType::UByte>>(200, 100, imaGL::CImaGL("test-gray.jpg"), "test-gray.jpg");
}

TEST_CASE("Opening a JPEG file from memory", "[opening-jpeg-from-memory]")
{
  using namespace imaGL::string_literals;

  std::ifstream ifs("test-rgb.jpg", std::ios::in | std::ios::binary);
  REQUIRE(ifs.is_open());

  //Read all content of the file
  ifs.seekg(0, std::ios::end);
  size_t length = ifs.tellg();
  ifs.seekg(0, std::ios::beg);
  std::string buffer(length, '\0');
  ifs.read(buffer.data(), length);

  //Encapsulate raw buffer in a stream buffer
  std::istringstream iss(std::move(buffer), std::ios::in | std::ios::binary);

  //Try to open from a JPG
  imaGL::CImaGL imgJPG(iss, "JPG "_FF);
  test_reading<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGBA, imaGL::CImaGL::EPixelType::UShort>>(200, 100, imgJPG, "test-rgb.jpg");

  //Try to open from an unknown type
  iss.seekg(0, std::ios::beg);
  imaGL::CImaGL imgUnknown(iss);
  test_reading<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGBA, imaGL::CImaGL::EPixelType::UShort>>(200, 100, imgUnknown, "test-rgb.jpg");
}
