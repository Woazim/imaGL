#pragma once

#include <vector>
#include <string_view>
#include <iostream>
#include <memory>
#ifdef __cpp_impl_three_way_comparison
#include <compare>
#endif

#if defined(_MSC_VER)
  //  Microsoft 
#ifdef IMAGL_STATIC
  #define EXPORT
  #define IMPORT
#else
  #define EXPORT __declspec(dllexport)
  #define IMPORT __declspec(dllimport)
#endif // _LIB
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

#ifdef ImaGL_EXPORTS
  #define IMAGL_API EXPORT
#else
  #define IMAGL_API IMPORT
#endif

namespace ImaGL {

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

  struct SPrivateImaGLData;

  class CFileFormat
  {
    uint32_t m_sig;
  public:
    CFileFormat(const char typeSig[4]) {
      m_sig = *reinterpret_cast<const uint32_t*>(typeSig);
    }
    CFileFormat(uint32_t typeSig) {
      m_sig = typeSig;
    }
    explicit operator uint32_t() {
      return m_sig;
    }
    explicit operator const char* (){
      return reinterpret_cast<const char*>(&m_sig);
    }
    explicit operator ::std::string() {
      return ::std::string(static_cast<const char*>(*this), 4);
    }
#ifdef __cpp_impl_three_way_comparison
    std::strong_ordering operator<=>(const CFileFormat&) const = default;
#else
    bool operator<(const CFileFormat& ff) const { return m_sig < ff.m_sig; }
    bool operator>(const CFileFormat& ff) const { return m_sig > ff.m_sig; }
    bool operator==(const CFileFormat& ff) const { return m_sig == ff.m_sig; }
#endif
  };

  class bad_format : public ::std::runtime_error {
  public:
    bad_format(const char* message) : ::std::runtime_error(message) {}
  };

  class loader_not_found : public ::std::runtime_error {
  public:
    loader_not_found(CFileFormat ff) :
      ::std::runtime_error("Loader for type " + static_cast<std::string>(ff) + " not found!")
    {}
  };

  class compatible_loader_not_found : public ::std::runtime_error {
  public:
    compatible_loader_not_found() :
      ::std::runtime_error("Compatbile loader has not been found!")
    {}
  };

  class IMAGL_API CImaGL
  {
  public:
    enum class EPixelFormat : unsigned int
    {
      Undefined = 0,
      R     = 0x1903, //GL_RED
      RG    = 0x8227, //GL_RG
      RGB   = 0x1907, //GL_RGB
      BGR   = 0x80E0, //GL_BGR
      RGBA  = 0x1908, //GL_RGBA
      BGRA  = 0x80E1  //GL_BGRA
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
    SPrivateImaGLData* m_pData;
    int m_nPixelSize = 0;

    void computePixelSize();

  public:
    CImaGL(std::string_view filename);
    CImaGL(std::istream& is, CFileFormat format);
    ~CImaGL();

    const unsigned char*  pixels()      const;
    size_t                width()       const;
    size_t                height()      const;
    EPixelFormat          pixelformat() const;
    EPixelType            pixeltype()   const;
    size_t                pixelsize()   const;

    void rescale(int width, int height);
    void rescaleToNextPowerOfTwo();
  };

  inline std::ostream& operator<<(std::ostream& os, const CImaGL::EPixelFormat& pf)
  {
    switch (pf)
    {
    case CImaGL::EPixelFormat::Undefined:
      return os << "Undefined";
    case CImaGL::EPixelFormat::R:
      return os << "R";
    case CImaGL::EPixelFormat::RG:
      return os << "RG";
    case CImaGL::EPixelFormat::RGB:
      return os << "RGB";
    case CImaGL::EPixelFormat::BGR:
      return os << "BGR";
    case CImaGL::EPixelFormat::RGBA:
      return os << "RGBA";
    case CImaGL::EPixelFormat::BGRA:
      return os << "BGRA";
    default:
      return os << "Unknown!";
    }
  }

  inline std::ostream& operator<<(std::ostream& os, const CImaGL::EPixelType& pf)
  {
    switch (pf)
    {
    case CImaGL::EPixelType::Undefined:
      return os << "Undefined";
    case CImaGL::EPixelType::UByte:
      return os << "UByte";
    case CImaGL::EPixelType::Byte:
      return os << "Byte";
    case CImaGL::EPixelType::UShort:
      return os << "UShort";
    case CImaGL::EPixelType::Short:
      return os << "Short";
    case CImaGL::EPixelType::UInt:
      return os << "UInt";
    case CImaGL::EPixelType::Int:
      return os << "Int";
    case CImaGL::EPixelType::HFloat:
      return os << "HFloat";
    case CImaGL::EPixelType::Float:
      return os << "Float";
    case CImaGL::EPixelType::UByte_3_3_2:
      return os << "UByte_3_3_2";
    case CImaGL::EPixelType::UByte_2_3_3_Rev:
      return os << "UByte_2_3_3_Rev";
    case CImaGL::EPixelType::UShort_5_6_5:
      return os << "UShort_5_6_5";
    case CImaGL::EPixelType::UShort_5_6_5_Rev:
      return os << "UShort_5_6_5_Rev";
    case CImaGL::EPixelType::UShort_4_4_4_4:
      return os << "UShort_4_4_4_4";
    case CImaGL::EPixelType::UShort_4_4_4_4_Rev:
      return os << "UShort_4_4_4_4_Rev";
    case CImaGL::EPixelType::UShort_5_5_5_1:
      return os << "UShort_5_5_5_1";
    case CImaGL::EPixelType::UShort_1_5_5_5_Rev:
      return os << "UShort_1_5_5_5_Rev";
    case CImaGL::EPixelType::UInt_8_8_8_8:
      return os << "UInt_8_8_8_8";
    case CImaGL::EPixelType::UInt_8_8_8_8_Rev:
      return os << "UInt_8_8_8_8_Rev";
    case CImaGL::EPixelType::UInt_10_10_10_2:
      return os << "UInt_10_10_10_2";
    case CImaGL::EPixelType::UInt_2_10_10_10_Rev:
      return os << "UInt_2_10_10_10_Rev";
    default:
      return os << "Unknown!";
    }
  }

  template<typename TYPE, CImaGL::EPixelType PACKING>
  class PackedPixel3Comp
  {
    TYPE pixel;
  public:
    inline TYPE comp1() const;
    inline TYPE comp2() const;
    inline TYPE comp3() const;
  };

  template<> inline unsigned char PackedPixel3Comp<unsigned char, CImaGL::EPixelType::UByte_3_3_2>::comp1() const { return pixel >> 5; }
  template<> inline unsigned char PackedPixel3Comp<unsigned char, CImaGL::EPixelType::UByte_3_3_2>::comp2() const { return (pixel & 0b00011100) >> 2; }
  template<> inline unsigned char PackedPixel3Comp<unsigned char, CImaGL::EPixelType::UByte_3_3_2>::comp3() const { return pixel & 0b00000011; }

  template<> inline unsigned char PackedPixel3Comp<unsigned char, CImaGL::EPixelType::UByte_2_3_3_Rev>::comp1() const { return pixel & 0b00000111; }
  template<> inline unsigned char PackedPixel3Comp<unsigned char, CImaGL::EPixelType::UByte_2_3_3_Rev>::comp2() const { return (pixel & 0b00111000) >> 3; }
  template<> inline unsigned char PackedPixel3Comp<unsigned char, CImaGL::EPixelType::UByte_2_3_3_Rev>::comp3() const { return pixel >> 6; }

  template<> inline unsigned short PackedPixel3Comp<unsigned short, CImaGL::EPixelType::UShort_5_6_5>::comp1() const { return pixel >> 11; }
  template<> inline unsigned short PackedPixel3Comp<unsigned short, CImaGL::EPixelType::UShort_5_6_5>::comp2() const { return (pixel & 0b0000011111100000) >> 5; }
  template<> inline unsigned short PackedPixel3Comp<unsigned short, CImaGL::EPixelType::UShort_5_6_5>::comp3() const { return pixel & 0b0000000000011111; }

  template<> inline unsigned short PackedPixel3Comp<unsigned short, CImaGL::EPixelType::UShort_5_6_5_Rev>::comp1() const { return pixel & 0b0000000000011111; }
  template<> inline unsigned short PackedPixel3Comp<unsigned short, CImaGL::EPixelType::UShort_5_6_5_Rev>::comp2() const { return (pixel & 0b0000011111100000) >> 5; }
  template<> inline unsigned short PackedPixel3Comp<unsigned short, CImaGL::EPixelType::UShort_5_6_5_Rev>::comp3() const { return pixel >> 11; }

  template<typename TYPE, CImaGL::EPixelType PACKING>
  class PackedPixel4Comp
  {
    TYPE pixel;
  public:
    inline TYPE comp1() const;
    inline TYPE comp2() const;
    inline TYPE comp3() const;
    inline TYPE comp4() const;
  };

  template<> inline unsigned short PackedPixel4Comp<unsigned short, CImaGL::EPixelType::UShort_4_4_4_4>::comp1() const { return pixel >> 12; }
  template<> inline unsigned short PackedPixel4Comp<unsigned short, CImaGL::EPixelType::UShort_4_4_4_4>::comp2() const { return (pixel & 0b0000111100000000) >> 8; }
  template<> inline unsigned short PackedPixel4Comp<unsigned short, CImaGL::EPixelType::UShort_4_4_4_4>::comp3() const { return (pixel & 0b0000000011110000) >> 4; }
  template<> inline unsigned short PackedPixel4Comp<unsigned short, CImaGL::EPixelType::UShort_4_4_4_4>::comp4() const { return (pixel & 0b0000000000001111); }

  template<> inline unsigned short PackedPixel4Comp<unsigned short, CImaGL::EPixelType::UShort_4_4_4_4_Rev>::comp1() const { return (pixel & 0b0000000000001111); }
  template<> inline unsigned short PackedPixel4Comp<unsigned short, CImaGL::EPixelType::UShort_4_4_4_4_Rev>::comp2() const { return (pixel & 0b0000000011110000) >> 4; }
  template<> inline unsigned short PackedPixel4Comp<unsigned short, CImaGL::EPixelType::UShort_4_4_4_4_Rev>::comp3() const { return (pixel & 0b0000111100000000) >> 8; }
  template<> inline unsigned short PackedPixel4Comp<unsigned short, CImaGL::EPixelType::UShort_4_4_4_4_Rev>::comp4() const { return pixel >> 12; }

  template<> inline unsigned short PackedPixel4Comp<unsigned short, CImaGL::EPixelType::UShort_5_5_5_1>::comp1() const { return pixel >> 11; }
  template<> inline unsigned short PackedPixel4Comp<unsigned short, CImaGL::EPixelType::UShort_5_5_5_1>::comp2() const { return (pixel & 0b0000011111000000) >> 6; }
  template<> inline unsigned short PackedPixel4Comp<unsigned short, CImaGL::EPixelType::UShort_5_5_5_1>::comp3() const { return (pixel & 0b0000000000111110) >> 1; }
  template<> inline unsigned short PackedPixel4Comp<unsigned short, CImaGL::EPixelType::UShort_5_5_5_1>::comp4() const { return (pixel & 0b0000000000000001); }

  template<> inline unsigned short PackedPixel4Comp<unsigned short, CImaGL::EPixelType::UShort_1_5_5_5_Rev>::comp1() const { return (pixel & 0b0000000000011111); }
  template<> inline unsigned short PackedPixel4Comp<unsigned short, CImaGL::EPixelType::UShort_1_5_5_5_Rev>::comp2() const { return (pixel & 0b0000001111100000) >> 5; }
  template<> inline unsigned short PackedPixel4Comp<unsigned short, CImaGL::EPixelType::UShort_1_5_5_5_Rev>::comp3() const { return (pixel & 0b0111110000000000) >> 10; }
  template<> inline unsigned short PackedPixel4Comp<unsigned short, CImaGL::EPixelType::UShort_1_5_5_5_Rev>::comp4() const { return pixel >> 15; }

  template<> inline unsigned int PackedPixel4Comp<unsigned int, CImaGL::EPixelType::UInt_8_8_8_8>::comp1() const { return pixel >> 24; }
  template<> inline unsigned int PackedPixel4Comp<unsigned int, CImaGL::EPixelType::UInt_8_8_8_8>::comp2() const { return (pixel & 0b00000000111111110000000000000000U) >> 16; }
  template<> inline unsigned int PackedPixel4Comp<unsigned int, CImaGL::EPixelType::UInt_8_8_8_8>::comp3() const { return (pixel & 0b00000000000000001111111100000000U) >> 8; }
  template<> inline unsigned int PackedPixel4Comp<unsigned int, CImaGL::EPixelType::UInt_8_8_8_8>::comp4() const { return (pixel & 0b00000000000000000000000011111111U); }

  template<> inline unsigned int PackedPixel4Comp<unsigned int, CImaGL::EPixelType::UInt_8_8_8_8_Rev>::comp1() const { return (pixel & 0b00000000000000000000000011111111U); }
  template<> inline unsigned int PackedPixel4Comp<unsigned int, CImaGL::EPixelType::UInt_8_8_8_8_Rev>::comp2() const { return (pixel & 0b00000000000000001111111100000000U) >> 8; }
  template<> inline unsigned int PackedPixel4Comp<unsigned int, CImaGL::EPixelType::UInt_8_8_8_8_Rev>::comp3() const { return (pixel & 0b00000000111111110000000000000000U) >> 16; }
  template<> inline unsigned int PackedPixel4Comp<unsigned int, CImaGL::EPixelType::UInt_8_8_8_8_Rev>::comp4() const { return pixel >> 24; }

  template<> inline unsigned int PackedPixel4Comp<unsigned int, CImaGL::EPixelType::UInt_10_10_10_2>::comp1() const { return pixel >> 22; }
  template<> inline unsigned int PackedPixel4Comp<unsigned int, CImaGL::EPixelType::UInt_10_10_10_2>::comp2() const { return (pixel & 0b00000000001111111111000000000000U) >> 12; }
  template<> inline unsigned int PackedPixel4Comp<unsigned int, CImaGL::EPixelType::UInt_10_10_10_2>::comp3() const { return (pixel & 0b00000000000000000000111111111100U) >> 2; }
  template<> inline unsigned int PackedPixel4Comp<unsigned int, CImaGL::EPixelType::UInt_10_10_10_2>::comp4() const { return (pixel & 0b00000000000000000000000000000011U); }

  template<> inline unsigned int PackedPixel4Comp<unsigned int, CImaGL::EPixelType::UInt_2_10_10_10_Rev>::comp1() const { return (pixel & 0b00000000000000000000001111111111U); }
  template<> inline unsigned int PackedPixel4Comp<unsigned int, CImaGL::EPixelType::UInt_2_10_10_10_Rev>::comp2() const { return (pixel & 0b00000000000011111111110000000000U) >> 10; }
  template<> inline unsigned int PackedPixel4Comp<unsigned int, CImaGL::EPixelType::UInt_2_10_10_10_Rev>::comp3() const { return (pixel & 0b00111111111100000000000000000000U) >> 20; }
  template<> inline unsigned int PackedPixel4Comp<unsigned int, CImaGL::EPixelType::UInt_2_10_10_10_Rev>::comp4() const { return pixel >> 30; }

}