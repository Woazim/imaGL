// test.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//
#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() 

#include "test.h"
#include <sstream>


TEST_CASE("Moving a CImaGL to another", "[move-constructor]")
{
  imaGL::CImaGL imgMoveFrom("test-16b.png");
  imaGL::CImaGL imgMoveTo(std::move(imgMoveFrom));

  test_reading<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGBA, imaGL::CImaGL::EPixelType::UShort>>(200, 100, imgMoveTo, "test-16b.png");
  CHECK(imgMoveFrom.pixelformat() == imaGL::CImaGL::EPixelFormat::Undefined);
  CHECK(imgMoveFrom.pixeltype() == imaGL::CImaGL::EPixelType::Undefined);
  CHECK(imgMoveFrom.pixelsize() == 0);
  CHECK(imgMoveFrom.pixels() == nullptr);
  CHECK(imgMoveFrom.nb_comp() == 0);
  CHECK(imgMoveFrom.width() == 0);
  CHECK(imgMoveFrom.height() == 0);

  imgMoveFrom = std::move(imgMoveTo);
  test_reading<imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGBA, imaGL::CImaGL::EPixelType::UShort>>(200, 100, imgMoveFrom, "test-16b.png");
  CHECK(imgMoveTo.pixelformat() == imaGL::CImaGL::EPixelFormat::Undefined);
  CHECK(imgMoveTo.pixeltype() == imaGL::CImaGL::EPixelType::Undefined);
  CHECK(imgMoveTo.pixelsize() == 0);
  CHECK(imgMoveTo.pixels() == nullptr);
  CHECK(imgMoveTo.nb_comp() == 0);
  CHECK(imgMoveTo.width() == 0);
  CHECK(imgMoveTo.height() == 0);
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