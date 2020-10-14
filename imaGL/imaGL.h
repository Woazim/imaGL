#pragma once

#include <vector>
#include <string_view>
#include <istream>

#if defined(_MSC_VER)
  //  Microsoft 
  #define EXPORT __declspec(dllexport)
  #define IMPORT __declspec(dllimport)
#elif defined(__GNUC__)
  //  GCC
  #define EXPORT __attribute__((visibility("default")))
  #define IMPORT
#else
  //  do nothing and hope for the best?
  #define EXPORT
  #define IMPORT
  #pragma warning Unknown dynamic link import/export semantics.
#endif

#ifdef BUILD_IMAGL
  #define IMAGL_API EXPORT
#else
  #define IMAGL_API IMPORT
#endif

template<typename pixeltype>
struct Pixel1Comp {
  pixeltype comp1;
};

template<typename pixeltype>
struct Pixel2Comp {
  pixeltype comp1;
  pixeltype comp2;
};

template<typename pixeltype>
struct Pixel3Comp {
  pixeltype comp1;
  pixeltype comp2;
  pixeltype comp3;
};

template<typename pixeltype>
struct Pixel4Comp {
  pixeltype comp1;
  pixeltype comp2;
  pixeltype comp3;
  pixeltype comp4;
};

class IMAGL_API CImaGL
{
public:
  enum class EPixelFormat : unsigned int
  {
    Undefined = 0,
    R         = 0x1903, //GL_RED
    RG        = 0x8227, //GL_RG
    RGB       = 0x1907, //GL_RGB
    BGR       = 0x80E0, //GL_BGR
    RGBA      = 0x1908, //GL_RGBA
    BGRA      = 0x80E1  //GL_BGRA
  };
  enum class EPixelType : unsigned int
  {
    Undefined           = 0,
    UByte               = 0x1401, //GL_UNSIGNED_BYTE
    Byte                = 0x1400, //GL_BYTE
    UShort              = 0x1403, //GL_UNSIGNED_SHORT
    Short               = 0x1402, //GL_SHORT
    UInt                = 0x1405, //GL_UNSIGNED_INT
    Int                 = 0x1404, //GL_INT
    HFloat              = 0x140B, //GL_HALF_FLOAT
    Float               = 0x1406, //GL_FLOAT
    UByte_3_3_2         = 0x8032, //GL_UNSIGNED_BYTE_3_3_2
    UByte_2_3_3_Rev     = 0x8362, //GL_UNSIGNED_BYTE_2_3_3_REV
    UShort_5_6_5        = 0x8363, //GL_UNSIGNED_SHORT_5_6_5
    UShort_5_6_5_Rev    = 0x8364, //GL_UNSIGNED_SHORT_5_6_5_REV
    UShort_4_4_4_4      = 0x8033, //GL_UNSIGNED_SHORT_4_4_4_4
    UShort_4_4_4_4_Rev  = 0x8365, //GL_UNSIGNED_SHORT_4_4_4_4_REV
    UShort_5_5_5_1      = 0x8034, //GL_UNSIGNED_SHORT_5_5_5_1
    UShort_1_5_5_5_Rev  = 0x8366, //GL_UNSIGNED_SHORT_1_5_5_5_REV
    UInt_8_8_8_8        = 0x8035, //GL_UNSIGNED_INT_8_8_8_8
    UInt_8_8_8_8_Rev    = 0x8367, //GL_UNSIGNED_INT_8_8_8_8_REV
    UInt_10_10_10_2     = 0x8036, //GL_UNSIGNED_INT_10_10_10_2
    UInt_2_10_10_10_Rev = 0x8368  //GL_UNSIGNED_INT_2_10_10_10_REV
  };

private:
  std::vector<unsigned char> m_vRawData;
  int m_nWidth = 0;
  int m_nHeight = 0;
  EPixelFormat m_PixelFormat = EPixelFormat::Undefined;
  EPixelType   m_PixelType = EPixelType::Undefined;
  int m_nPixelSize = 0;

  void computePixelSize();


public:
  CImaGL(std::string_view filename);
  CImaGL(std::istream& is);

  const unsigned char*  pixels()      const { return m_vRawData.data(); }
  int                   width()       const { return m_nWidth; }
  int                   height()      const { return m_nHeight; }
  EPixelFormat          pixelformat() const { return m_PixelFormat; }
  EPixelType            pixeltype()   const { return m_PixelType; }
  int                   pixelsize()   const { return m_nPixelSize; }

  void rescale(int width, int height);
  void rescaleToNextPowerOfTwo();
};

template<typename TYPE, CImaGL::EPixelType PACKING>
class PackedPixel3Comp
{
  TYPE pixel;
public:
  TYPE comp1() const;
  TYPE comp2() const;
  TYPE comp3() const;
};

template<> unsigned char PackedPixel3Comp<unsigned char, CImaGL::EPixelType::UByte_3_3_2>::comp1() const { return pixel >> 5; }
template<> unsigned char PackedPixel3Comp<unsigned char, CImaGL::EPixelType::UByte_3_3_2>::comp2() const { return (pixel & 0b00011100) >> 2; }
template<> unsigned char PackedPixel3Comp<unsigned char, CImaGL::EPixelType::UByte_3_3_2>::comp3() const { return pixel & 0b00000011; }

template<> unsigned char PackedPixel3Comp<unsigned char, CImaGL::EPixelType::UByte_2_3_3_Rev>::comp1() const { return pixel & 0b00000111; }
template<> unsigned char PackedPixel3Comp<unsigned char, CImaGL::EPixelType::UByte_2_3_3_Rev>::comp2() const { return (pixel & 0b00111000) >> 3; }
template<> unsigned char PackedPixel3Comp<unsigned char, CImaGL::EPixelType::UByte_2_3_3_Rev>::comp3() const { return pixel >> 6; }

template<> unsigned short PackedPixel3Comp<unsigned short, CImaGL::EPixelType::UShort_5_6_5>::comp1() const { return pixel >> 11; }
template<> unsigned short PackedPixel3Comp<unsigned short, CImaGL::EPixelType::UShort_5_6_5>::comp2() const { return (pixel & 0b0000011111100000) >> 5; }
template<> unsigned short PackedPixel3Comp<unsigned short, CImaGL::EPixelType::UShort_5_6_5>::comp3() const { return pixel & 0b0000000000011111; }

template<> unsigned short PackedPixel3Comp<unsigned short, CImaGL::EPixelType::UShort_5_6_5_Rev>::comp1() const { return pixel & 0b0000000000011111; }
template<> unsigned short PackedPixel3Comp<unsigned short, CImaGL::EPixelType::UShort_5_6_5_Rev>::comp2() const { return (pixel & 0b0000011111100000) >> 5; }
template<> unsigned short PackedPixel3Comp<unsigned short, CImaGL::EPixelType::UShort_5_6_5_Rev>::comp3() const { return pixel >> 11; }

template<typename TYPE, CImaGL::EPixelType PACKING>
class PackedPixel4Comp
{
  TYPE pixel;
public:
  TYPE comp1() const;
  TYPE comp2() const;
  TYPE comp3() const;
  TYPE comp4() const;
};

template<> unsigned short PackedPixel4Comp<unsigned short, CImaGL::EPixelType::UShort_4_4_4_4>::comp1() const { return pixel >> 12; }
template<> unsigned short PackedPixel4Comp<unsigned short, CImaGL::EPixelType::UShort_4_4_4_4>::comp2() const { return (pixel & 0b0000111100000000) >> 8; }
template<> unsigned short PackedPixel4Comp<unsigned short, CImaGL::EPixelType::UShort_4_4_4_4>::comp3() const { return (pixel & 0b0000000011110000) >> 4; }
template<> unsigned short PackedPixel4Comp<unsigned short, CImaGL::EPixelType::UShort_4_4_4_4>::comp4() const { return (pixel & 0b0000000000001111); }

template<> unsigned short PackedPixel4Comp<unsigned short, CImaGL::EPixelType::UShort_4_4_4_4_Rev>::comp1() const { return (pixel & 0b0000000000001111); }
template<> unsigned short PackedPixel4Comp<unsigned short, CImaGL::EPixelType::UShort_4_4_4_4_Rev>::comp2() const { return (pixel & 0b0000000011110000) >> 4; }
template<> unsigned short PackedPixel4Comp<unsigned short, CImaGL::EPixelType::UShort_4_4_4_4_Rev>::comp3() const { return (pixel & 0b0000111100000000) >> 8; }
template<> unsigned short PackedPixel4Comp<unsigned short, CImaGL::EPixelType::UShort_4_4_4_4_Rev>::comp4() const { return pixel >> 12; }

template<> unsigned short PackedPixel4Comp<unsigned short, CImaGL::EPixelType::UShort_5_5_5_1>::comp1() const { return pixel >> 11; }
template<> unsigned short PackedPixel4Comp<unsigned short, CImaGL::EPixelType::UShort_5_5_5_1>::comp2() const { return (pixel & 0b0000011111000000) >> 6; }
template<> unsigned short PackedPixel4Comp<unsigned short, CImaGL::EPixelType::UShort_5_5_5_1>::comp3() const { return (pixel & 0b0000000000111110) >> 1; }
template<> unsigned short PackedPixel4Comp<unsigned short, CImaGL::EPixelType::UShort_5_5_5_1>::comp4() const { return (pixel & 0b0000000000000001); }

template<> unsigned short PackedPixel4Comp<unsigned short, CImaGL::EPixelType::UShort_1_5_5_5_Rev>::comp1() const { return (pixel & 0b0000000000011111); }
template<> unsigned short PackedPixel4Comp<unsigned short, CImaGL::EPixelType::UShort_1_5_5_5_Rev>::comp2() const { return (pixel & 0b0000001111100000) >> 5; }
template<> unsigned short PackedPixel4Comp<unsigned short, CImaGL::EPixelType::UShort_1_5_5_5_Rev>::comp3() const { return (pixel & 0b0111110000000000) >> 10; }
template<> unsigned short PackedPixel4Comp<unsigned short, CImaGL::EPixelType::UShort_1_5_5_5_Rev>::comp4() const { return pixel >> 15; }

template<> unsigned int PackedPixel4Comp<unsigned int, CImaGL::EPixelType::UInt_8_8_8_8>::comp1() const { return pixel >> 24; }
template<> unsigned int PackedPixel4Comp<unsigned int, CImaGL::EPixelType::UInt_8_8_8_8>::comp2() const { return (pixel & 0b00000000111111110000000000000000U) >> 16; }
template<> unsigned int PackedPixel4Comp<unsigned int, CImaGL::EPixelType::UInt_8_8_8_8>::comp3() const { return (pixel & 0b00000000000000001111111100000000U) >> 8; }
template<> unsigned int PackedPixel4Comp<unsigned int, CImaGL::EPixelType::UInt_8_8_8_8>::comp4() const { return (pixel & 0b00000000000000000000000011111111U); }

template<> unsigned int PackedPixel4Comp<unsigned int, CImaGL::EPixelType::UInt_8_8_8_8_Rev>::comp1() const { return (pixel & 0b00000000000000000000000011111111U); }
template<> unsigned int PackedPixel4Comp<unsigned int, CImaGL::EPixelType::UInt_8_8_8_8_Rev>::comp2() const { return (pixel & 0b00000000000000001111111100000000U) >> 8; }
template<> unsigned int PackedPixel4Comp<unsigned int, CImaGL::EPixelType::UInt_8_8_8_8_Rev>::comp3() const { return (pixel & 0b00000000111111110000000000000000U) >> 16; }
template<> unsigned int PackedPixel4Comp<unsigned int, CImaGL::EPixelType::UInt_8_8_8_8_Rev>::comp4() const { return pixel >> 24; }

template<> unsigned int PackedPixel4Comp<unsigned int, CImaGL::EPixelType::UInt_10_10_10_2>::comp1() const { return pixel >> 22; }
template<> unsigned int PackedPixel4Comp<unsigned int, CImaGL::EPixelType::UInt_10_10_10_2>::comp2() const { return (pixel & 0b00000000001111111111000000000000U) >> 12; }
template<> unsigned int PackedPixel4Comp<unsigned int, CImaGL::EPixelType::UInt_10_10_10_2>::comp3() const { return (pixel & 0b00000000000000000000111111111100U) >> 2; }
template<> unsigned int PackedPixel4Comp<unsigned int, CImaGL::EPixelType::UInt_10_10_10_2>::comp4() const { return (pixel & 0b00000000000000000000000000000011U); }

template<> unsigned int PackedPixel4Comp<unsigned int, CImaGL::EPixelType::UInt_2_10_10_10_Rev>::comp1() const { return (pixel & 0b00000000000000000000001111111111U); }
template<> unsigned int PackedPixel4Comp<unsigned int, CImaGL::EPixelType::UInt_2_10_10_10_Rev>::comp2() const { return (pixel & 0b00000000000011111111110000000000U) >> 10; }
template<> unsigned int PackedPixel4Comp<unsigned int, CImaGL::EPixelType::UInt_2_10_10_10_Rev>::comp3() const { return (pixel & 0b00111111111100000000000000000000U) >> 20; }
template<> unsigned int PackedPixel4Comp<unsigned int, CImaGL::EPixelType::UInt_2_10_10_10_Rev>::comp4() const { return pixel >> 30; }
