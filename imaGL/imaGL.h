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
      ::std::runtime_error("Compatible loader has not been found!")
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

    void upscale_x(const SPrivateImaGLData& source, SPrivateImaGLData& dest);
    void downscale_x(const SPrivateImaGLData& source, SPrivateImaGLData& dest);
    void downscale_x_by2(const SPrivateImaGLData& source, SPrivateImaGLData& dest);
    void upscale_y(const SPrivateImaGLData& source, SPrivateImaGLData& dest);
    void downscale_y(const SPrivateImaGLData& source, SPrivateImaGLData& dest);

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

  constexpr size_t computePixelSize(CImaGL::EPixelFormat pf, CImaGL::EPixelType pt)
  {
    int nNbComp = 0;
    switch (pf)
    {
    default:
    case CImaGL::EPixelFormat::Undefined:
      return 0;
    case CImaGL::EPixelFormat::R:
      nNbComp = 1;
      break;
    case CImaGL::EPixelFormat::RG:
      nNbComp = 2;
      break;
    case CImaGL::EPixelFormat::RGB:
    case CImaGL::EPixelFormat::BGR:
      nNbComp = 3;
      break;
    case CImaGL::EPixelFormat::RGBA:
    case CImaGL::EPixelFormat::BGRA:
      nNbComp = 4;
      break;
    }
    switch (pt)
    {
    default:
    case CImaGL::EPixelType::Undefined:
      return 0;
    case CImaGL::EPixelType::UByte:
    case CImaGL::EPixelType::Byte:
      return nNbComp;
    case CImaGL::EPixelType::UShort:
    case CImaGL::EPixelType::Short:
      return nNbComp * 2;
    case CImaGL::EPixelType::UInt:
    case CImaGL::EPixelType::Int:
      return nNbComp * 4;
    case CImaGL::EPixelType::HFloat:
      return nNbComp * 2;
    case CImaGL::EPixelType::Float:
      return nNbComp * 4;
    case CImaGL::EPixelType::UByte_3_3_2:
    case CImaGL::EPixelType::UByte_2_3_3_Rev:
      return 1;
    case CImaGL::EPixelType::UShort_5_6_5:
    case CImaGL::EPixelType::UShort_5_6_5_Rev:
      return 2;
    case CImaGL::EPixelType::UShort_4_4_4_4:
    case CImaGL::EPixelType::UShort_4_4_4_4_Rev:
    case CImaGL::EPixelType::UShort_5_5_5_1:
    case CImaGL::EPixelType::UShort_1_5_5_5_Rev:
    case CImaGL::EPixelType::UInt_8_8_8_8:
    case CImaGL::EPixelType::UInt_8_8_8_8_Rev:
    case CImaGL::EPixelType::UInt_10_10_10_2:
    case CImaGL::EPixelType::UInt_2_10_10_10_Rev:
      return 4;
    }
    return 0;
  }

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

  template<CImaGL::EPixelType pt>
  struct Pack {
    using pixel_type = void*;
    using comp_type = void*;
    static const int nbComp = 0;
  };

  template<> struct Pack< CImaGL::EPixelType::UByte_3_3_2> {
    using pixel_type = unsigned char;
    using comp_type = unsigned char;
    static const int nbComp = 3;
  };
  template<> struct Pack< CImaGL::EPixelType::UByte_2_3_3_Rev> {
    using pixel_type = unsigned char;
    using comp_type = unsigned char;
    static const int nbComp = 3;
  };
  template<> struct Pack< CImaGL::EPixelType::UShort_5_5_5_1> {
    using pixel_type = unsigned short;
    using comp_type = unsigned char;
    static const int nbComp = 4;
  };
  template<> struct Pack< CImaGL::EPixelType::UShort_1_5_5_5_Rev> {
    using pixel_type = unsigned short;
    using comp_type = unsigned char;
    static const int nbComp = 4;
  };
  template<> struct Pack< CImaGL::EPixelType::UShort_4_4_4_4> {
    using pixel_type = unsigned short;
    using comp_type = unsigned char;
    static const int nbComp = 4;
  };
  template<> struct Pack< CImaGL::EPixelType::UShort_4_4_4_4_Rev> {
    using pixel_type = unsigned short;
    using comp_type = unsigned char;
    static const int nbComp = 4;
  };
  template<> struct Pack< CImaGL::EPixelType::UShort_5_6_5> {
    using pixel_type = unsigned short;
    using comp_type = unsigned char;
    static const int nbComp = 3;
  };
  template<> struct Pack< CImaGL::EPixelType::UShort_5_6_5_Rev> {
    using pixel_type = unsigned short;
    using comp_type = unsigned char;
    static const int nbComp = 3;
  };
  template<> struct Pack< CImaGL::EPixelType::UInt_10_10_10_2> {
    using pixel_type = unsigned int;
    using comp_type = unsigned short;
    static const int nbComp = 4;
  };
  template<> struct Pack< CImaGL::EPixelType::UInt_2_10_10_10_Rev> {
    using pixel_type = unsigned int;
    using comp_type = unsigned short;
    static const int nbComp = 4;
  };
  template<> struct Pack< CImaGL::EPixelType::UInt_8_8_8_8> {
    using pixel_type = unsigned int;
    using comp_type = unsigned char;
    static const int nbComp = 4;
  };
  template<> struct Pack< CImaGL::EPixelType::UInt_8_8_8_8_Rev> {
    using pixel_type = unsigned int;
    using comp_type = unsigned char;
    static const int nbComp = 4;
  };

  template<CImaGL::EPixelType pt>
  class PackedPixel
  {
  public:
    using type = typename Pack<pt>::pixel_type;
    using comp_type = typename Pack<pt>::comp_type;
    static const int nb_comp = Pack<pt>::nbComp;
    inline static const uint32_t* componentMasks();
    inline static const int* componentShifts();
  private:
    type pixel;
  public:
    template<size_t n>
    comp_type comp() const { static_assert(n < nb_comp, "The component indice is not valid!"); return (pixel & componentMasks()[n]) >> componentShifts()[n]; }
    comp_type comp_i(size_t i) const {
      switch (i) {
      case 0:  return comp<0>();
      case 1:  return comp<1>();
      case 2:  return comp<2>();
      case 3:  return comp<3>();
      default: return comp<4>();
      }
    }
    template<size_t n>
    inline void comp(comp_type val) { throw std::logic_error("Not implemented! You definitly try to access a pixel component that doesn't exist."); }
    void comp_i(size_t i, comp_type val) const {
      switch (i) {
      case 0:  comp<0>(val); break;
      case 1:  comp<1>(val); break;
      case 2:  comp<2>(val); break;
      case 3:  comp<3>(val); break;
      default: comp<4>(val); break;
      }
    }
  };

  using PixelUByte_3_3_2 = PackedPixel<CImaGL::EPixelType::UByte_3_3_2>;
  template<> inline const uint32_t* PixelUByte_3_3_2::componentMasks() { static uint32_t data[] = { (uint8_t)-1, 0b00011100, 0b00000011 }; return data; }
  template<> inline const int* PixelUByte_3_3_2::componentShifts() { static int data[] = { 5, 2, 0 }; return data; }

  using PixelUByte_2_3_3_Rev = PackedPixel<CImaGL::EPixelType::UByte_2_3_3_Rev>;
  template<> inline const uint32_t* PixelUByte_2_3_3_Rev::componentMasks() { static uint32_t data[] = { 0b00000111, 0b00111000, (uint8_t)-1 }; return data; }
  template<> inline const int* PixelUByte_2_3_3_Rev::componentShifts() { static int data[] = { 0, 3, 6 }; return data; }

  using PixelUShort_5_6_5 = PackedPixel<CImaGL::EPixelType::UShort_5_6_5>;
  template<> inline const uint32_t* PixelUShort_5_6_5::componentMasks() { static uint32_t data[] = { (uint16_t)-1, 0b0000011111100000, 0b0000000000011111 }; return data; }
  template<> inline const int* PixelUShort_5_6_5::componentShifts() { static int data[] = { 11, 5, 0 }; return data; }

  using PixelUShort_5_6_5_Rev = PackedPixel<CImaGL::EPixelType::UShort_5_6_5_Rev>;
  template<> inline const uint32_t* PixelUShort_5_6_5_Rev::componentMasks() { static uint32_t data[] = { 0b0000000000011111, 0b0000011111100000, (uint16_t)-1 }; return data; }
  template<> inline const int* PixelUShort_5_6_5_Rev::componentShifts() { static int data[] = { 0, 5, 11 }; return data; }

  using PixelUShort_4_4_4_4 = PackedPixel<CImaGL::EPixelType::UShort_4_4_4_4>;
  template<> inline const uint32_t* PixelUShort_4_4_4_4::componentMasks() { static uint32_t data[] = { (uint16_t)-1, 0b0000111100000000, 0b0000000011110000, 0b0000000000001111 }; return data; }
  template<> inline const int* PixelUShort_4_4_4_4::componentShifts() { static int data[] = { 12, 8, 4, 0 }; return data; }

  using PixelUShort_4_4_4_4_Rev = PackedPixel<CImaGL::EPixelType::UShort_4_4_4_4_Rev>;
  template<> inline const uint32_t* PixelUShort_4_4_4_4_Rev::componentMasks() { static uint32_t data[] = { 0b0000000000001111, 0b0000000011110000, 0b0000111100000000, (uint16_t)-1 }; return data; }
  template<> inline const int* PixelUShort_4_4_4_4_Rev::componentShifts() { static int data[] = { 0, 4, 8, 12 }; return data; }

  using PixelUShort_5_5_5_1 = PackedPixel<CImaGL::EPixelType::UShort_5_5_5_1>;
  template<> inline const uint32_t* PixelUShort_5_5_5_1::componentMasks() { static uint32_t data[] = { (uint16_t)-1, 0b0000011111000000, 0b0000000000111110, 0b0000000000000001 }; return data; }
  template<> inline const int* PixelUShort_5_5_5_1::componentShifts() { static int data[] = { 11, 6, 1, 0 }; return data; }

  using PixelUShort_1_5_5_5_Rev = PackedPixel<CImaGL::EPixelType::UShort_1_5_5_5_Rev>;
  template<> inline const uint32_t* PixelUShort_1_5_5_5_Rev::componentMasks() { static uint32_t data[] = { 0b0000000000011111, 0b0000001111100000, 0b0111110000000000, (uint16_t)-1}; return data; }
  template<> inline const int* PixelUShort_1_5_5_5_Rev::componentShifts() { static int data[] = { 0, 5, 10, 15 }; return data; }

  using PixelUInt_8_8_8_8 = PackedPixel<CImaGL::EPixelType::UInt_8_8_8_8>;
  template<> inline const uint32_t* PixelUInt_8_8_8_8::componentMasks() { static uint32_t data[] = { (uint32_t)-1, 0b00000000111111110000000000000000U, 0b00000000000000001111111100000000U, 0b00000000000000000000000011111111U }; return data; }
  template<> inline const int* PixelUInt_8_8_8_8::componentShifts() { static int data[] = { 24, 16, 8, 0 }; return data; }

  using PixelUInt_8_8_8_8_Rev = PackedPixel<CImaGL::EPixelType::UInt_8_8_8_8_Rev>;
  template<> inline const uint32_t* PixelUInt_8_8_8_8_Rev::componentMasks() { static uint32_t data[] = { 0b00000000000000000000000011111111U, 0b00000000000000001111111100000000U, 0b00000000111111110000000000000000U, (uint32_t)-1 }; return data; }
  template<> inline const int* PixelUInt_8_8_8_8_Rev::componentShifts() { static int data[] = { 0, 8, 16, 24 }; return data; }

  using PixelUInt_10_10_10_2 = PackedPixel<CImaGL::EPixelType::UInt_10_10_10_2>;
  template<> inline const uint32_t* PixelUInt_10_10_10_2::componentMasks() { static uint32_t data[] = { (uint32_t)-1, 0b00000000001111111111000000000000U, 0b00000000000000000000111111111100U, 0b00000000000000000000000000000011U }; return data; }
  template<> inline const int* PixelUInt_10_10_10_2::componentShifts() { static int data[] = { 22, 12, 2, 0 }; return data; }

  using PixelUInt_2_10_10_10_Rev = PackedPixel<CImaGL::EPixelType::UInt_2_10_10_10_Rev>;
  template<> inline const uint32_t* PixelUInt_2_10_10_10_Rev::componentMasks() { static uint32_t data[] = { 0b00000000000000000000001111111111U, 0b00000000000011111111110000000000U, 0b00111111111100000000000000000000U, (uint32_t)-1 }; return data; }
  template<> inline const int* PixelUInt_2_10_10_10_Rev::componentShifts() { static int data[] = { 0, 10, 20, 30 }; return data; }

  template<CImaGL::EPixelFormat pf, CImaGL::EPixelType pt>
  struct Comp { using type = void; };

  template<> struct Comp<CImaGL::EPixelFormat::R, CImaGL::EPixelType::Byte> { using type = char; };
  template<> struct Comp<CImaGL::EPixelFormat::RG, CImaGL::EPixelType::Byte> { using type = char; };
  template<> struct Comp<CImaGL::EPixelFormat::RGB, CImaGL::EPixelType::Byte> { using type = char; };
  template<> struct Comp<CImaGL::EPixelFormat::RGBA, CImaGL::EPixelType::Byte> { using type = char; };
  template<> struct Comp<CImaGL::EPixelFormat::BGR, CImaGL::EPixelType::Byte> { using type = char; };
  template<> struct Comp<CImaGL::EPixelFormat::BGRA, CImaGL::EPixelType::Byte> { using type = char; };

  template<> struct Comp<CImaGL::EPixelFormat::R, CImaGL::EPixelType::Float> { using type = float; };
  template<> struct Comp<CImaGL::EPixelFormat::RG, CImaGL::EPixelType::Float> { using type = float; };
  template<> struct Comp<CImaGL::EPixelFormat::RGB, CImaGL::EPixelType::Float> { using type = float; };
  template<> struct Comp<CImaGL::EPixelFormat::RGBA, CImaGL::EPixelType::Float> { using type = float; };
  template<> struct Comp<CImaGL::EPixelFormat::BGR, CImaGL::EPixelType::Float> { using type = float; };
  template<> struct Comp<CImaGL::EPixelFormat::BGRA, CImaGL::EPixelType::Float> { using type = float; };

  template<> struct Comp<CImaGL::EPixelFormat::R, CImaGL::EPixelType::Int> { using type = int; };
  template<> struct Comp<CImaGL::EPixelFormat::RG, CImaGL::EPixelType::Int> { using type = int; };
  template<> struct Comp<CImaGL::EPixelFormat::RGB, CImaGL::EPixelType::Int> { using type = int; };
  template<> struct Comp<CImaGL::EPixelFormat::RGBA, CImaGL::EPixelType::Int> { using type = int; };
  template<> struct Comp<CImaGL::EPixelFormat::BGR, CImaGL::EPixelType::Int> { using type = int; };
  template<> struct Comp<CImaGL::EPixelFormat::BGRA, CImaGL::EPixelType::Int> { using type = int; };

  template<> struct Comp<CImaGL::EPixelFormat::R, CImaGL::EPixelType::Short> { using type = short; };
  template<> struct Comp<CImaGL::EPixelFormat::RG, CImaGL::EPixelType::Short> { using type = short; };
  template<> struct Comp<CImaGL::EPixelFormat::RGB, CImaGL::EPixelType::Short> { using type = short; };
  template<> struct Comp<CImaGL::EPixelFormat::RGBA, CImaGL::EPixelType::Short> { using type = short; };
  template<> struct Comp<CImaGL::EPixelFormat::BGR, CImaGL::EPixelType::Short> { using type = short; };
  template<> struct Comp<CImaGL::EPixelFormat::BGRA, CImaGL::EPixelType::Short> { using type = short; };

  template<> struct Comp<CImaGL::EPixelFormat::R, CImaGL::EPixelType::UByte> { using type = unsigned char; };
  template<> struct Comp<CImaGL::EPixelFormat::RG, CImaGL::EPixelType::UByte> { using type = unsigned char; };
  template<> struct Comp<CImaGL::EPixelFormat::RGB, CImaGL::EPixelType::UByte> { using type = unsigned char; };
  template<> struct Comp<CImaGL::EPixelFormat::RGBA, CImaGL::EPixelType::UByte> { using type = unsigned char; };
  template<> struct Comp<CImaGL::EPixelFormat::BGR, CImaGL::EPixelType::UByte> { using type = unsigned char; };
  template<> struct Comp<CImaGL::EPixelFormat::BGRA, CImaGL::EPixelType::UByte> { using type = unsigned char; };

  template<> struct Comp<CImaGL::EPixelFormat::R, CImaGL::EPixelType::UInt> { using type = unsigned int; };
  template<> struct Comp<CImaGL::EPixelFormat::RG, CImaGL::EPixelType::UInt> { using type = unsigned int; };
  template<> struct Comp<CImaGL::EPixelFormat::RGB, CImaGL::EPixelType::UInt> { using type = unsigned int; };
  template<> struct Comp<CImaGL::EPixelFormat::RGBA, CImaGL::EPixelType::UInt> { using type = unsigned int; };
  template<> struct Comp<CImaGL::EPixelFormat::BGR, CImaGL::EPixelType::UInt> { using type = unsigned int; };
  template<> struct Comp<CImaGL::EPixelFormat::BGRA, CImaGL::EPixelType::UInt> { using type = unsigned int; };

  template<> struct Comp<CImaGL::EPixelFormat::R, CImaGL::EPixelType::UShort> { using type = unsigned short; };
  template<> struct Comp<CImaGL::EPixelFormat::RG, CImaGL::EPixelType::UShort> { using type = unsigned short; };
  template<> struct Comp<CImaGL::EPixelFormat::RGB, CImaGL::EPixelType::UShort> { using type = unsigned short; };
  template<> struct Comp<CImaGL::EPixelFormat::RGBA, CImaGL::EPixelType::UShort> { using type = unsigned short; };
  template<> struct Comp<CImaGL::EPixelFormat::BGR, CImaGL::EPixelType::UShort> { using type = unsigned short; };
  template<> struct Comp<CImaGL::EPixelFormat::BGRA, CImaGL::EPixelType::UShort> { using type = unsigned short; };

  template<> struct Comp<CImaGL::EPixelFormat::RGB, CImaGL::EPixelType::UByte_2_3_3_Rev> { using type = Pack<CImaGL::EPixelType::UByte_2_3_3_Rev>::comp_type; };
  template<> struct Comp<CImaGL::EPixelFormat::BGR, CImaGL::EPixelType::UByte_2_3_3_Rev> { using type = Pack<CImaGL::EPixelType::UByte_2_3_3_Rev>::comp_type; };

  template<> struct Comp<CImaGL::EPixelFormat::RGB, CImaGL::EPixelType::UByte_3_3_2> { using type = Pack<CImaGL::EPixelType::UByte_3_3_2>::comp_type; };
  template<> struct Comp<CImaGL::EPixelFormat::BGR, CImaGL::EPixelType::UByte_3_3_2> { using type = Pack<CImaGL::EPixelType::UByte_3_3_2>::comp_type; };

  template<> struct Comp<CImaGL::EPixelFormat::RGBA, CImaGL::EPixelType::UInt_10_10_10_2> { using type = Pack<CImaGL::EPixelType::UInt_10_10_10_2>::comp_type; };
  template<> struct Comp<CImaGL::EPixelFormat::BGRA, CImaGL::EPixelType::UInt_10_10_10_2> { using type = Pack<CImaGL::EPixelType::UInt_10_10_10_2>::comp_type; };

  template<> struct Comp<CImaGL::EPixelFormat::RGBA, CImaGL::EPixelType::UInt_2_10_10_10_Rev> { using type = Pack<CImaGL::EPixelType::UInt_2_10_10_10_Rev>::comp_type; };
  template<> struct Comp<CImaGL::EPixelFormat::BGRA, CImaGL::EPixelType::UInt_2_10_10_10_Rev> { using type = Pack<CImaGL::EPixelType::UInt_2_10_10_10_Rev>::comp_type; };

  template<> struct Comp<CImaGL::EPixelFormat::RGBA, CImaGL::EPixelType::UInt_8_8_8_8> { using type = Pack<CImaGL::EPixelType::UInt_8_8_8_8>::comp_type; };
  template<> struct Comp<CImaGL::EPixelFormat::BGRA, CImaGL::EPixelType::UInt_8_8_8_8> { using type = Pack<CImaGL::EPixelType::UInt_8_8_8_8>::comp_type; };

  template<> struct Comp<CImaGL::EPixelFormat::RGBA, CImaGL::EPixelType::UInt_8_8_8_8_Rev> { using type = Pack<CImaGL::EPixelType::UInt_8_8_8_8_Rev>::comp_type; };
  template<> struct Comp<CImaGL::EPixelFormat::BGRA, CImaGL::EPixelType::UInt_8_8_8_8_Rev> { using type = Pack<CImaGL::EPixelType::UInt_8_8_8_8_Rev>::comp_type; };

  template<> struct Comp<CImaGL::EPixelFormat::RGBA, CImaGL::EPixelType::UShort_1_5_5_5_Rev> { using type = Pack<CImaGL::EPixelType::UShort_1_5_5_5_Rev>::comp_type; };
  template<> struct Comp<CImaGL::EPixelFormat::BGRA, CImaGL::EPixelType::UShort_1_5_5_5_Rev> { using type = Pack<CImaGL::EPixelType::UShort_1_5_5_5_Rev>::comp_type; };

  template<> struct Comp<CImaGL::EPixelFormat::RGBA, CImaGL::EPixelType::UShort_4_4_4_4> { using type = Pack<CImaGL::EPixelType::UShort_4_4_4_4>::comp_type; };
  template<> struct Comp<CImaGL::EPixelFormat::BGRA, CImaGL::EPixelType::UShort_4_4_4_4> { using type = Pack<CImaGL::EPixelType::UShort_4_4_4_4>::comp_type; };

  template<> struct Comp<CImaGL::EPixelFormat::RGBA, CImaGL::EPixelType::UShort_4_4_4_4_Rev> { using type = Pack<CImaGL::EPixelType::UShort_4_4_4_4_Rev>::comp_type; };
  template<> struct Comp<CImaGL::EPixelFormat::BGRA, CImaGL::EPixelType::UShort_4_4_4_4_Rev> { using type = Pack<CImaGL::EPixelType::UShort_4_4_4_4_Rev>::comp_type; };

  template<> struct Comp<CImaGL::EPixelFormat::RGBA, CImaGL::EPixelType::UShort_5_5_5_1> { using type = Pack<CImaGL::EPixelType::UShort_5_5_5_1>::comp_type; };
  template<> struct Comp<CImaGL::EPixelFormat::BGRA, CImaGL::EPixelType::UShort_5_5_5_1> { using type = Pack<CImaGL::EPixelType::UShort_5_5_5_1>::comp_type; };

  template<> struct Comp<CImaGL::EPixelFormat::RGB, CImaGL::EPixelType::UShort_5_6_5> { using type = Pack<CImaGL::EPixelType::UShort_5_6_5>::comp_type; };
  template<> struct Comp<CImaGL::EPixelFormat::BGR, CImaGL::EPixelType::UShort_5_6_5> { using type = Pack<CImaGL::EPixelType::UShort_5_6_5>::comp_type; };

  template<> struct Comp<CImaGL::EPixelFormat::RGB, CImaGL::EPixelType::UShort_5_6_5_Rev> { using type = Pack<CImaGL::EPixelType::UShort_5_6_5_Rev>::comp_type; };
  template<> struct Comp<CImaGL::EPixelFormat::BGR, CImaGL::EPixelType::UShort_5_6_5_Rev> { using type = Pack<CImaGL::EPixelType::UShort_5_6_5_Rev>::comp_type; };

  template<CImaGL::EPixelFormat pf>
  struct NbComp { static const size_t val = 0; };

  template<> struct NbComp<CImaGL::EPixelFormat::R>    { static const size_t val = 1; };
  template<> struct NbComp<CImaGL::EPixelFormat::RG>   { static const size_t val = 2; };
  template<> struct NbComp<CImaGL::EPixelFormat::RGB>  { static const size_t val = 3; };
  template<> struct NbComp<CImaGL::EPixelFormat::BGR>  { static const size_t val = 3; };
  template<> struct NbComp<CImaGL::EPixelFormat::RGBA> { static const size_t val = 4; };
  template<> struct NbComp<CImaGL::EPixelFormat::BGRA> { static const size_t val = 4; };

  template<CImaGL::EPixelFormat pf, CImaGL::EPixelType pt, size_t pixelsize = computePixelSize(pf, pt)>
  class Pixel {
    unsigned char m_pix[pixelsize];
  public:
    //Type information about this class
    using comp_type = typename Comp<pf, pt>::type;
    using pack_type = PackedPixel<pt>;
    //Static information about this class
    static constexpr CImaGL::EPixelFormat pixel_format() { return pf; }
    static constexpr CImaGL::EPixelType   pixel_type()   { return pt; }
    static constexpr size_t               pixel_size()   { return pixelsize; }
    static constexpr bool                 is_packed()    { return !std::is_pointer_v<typename pack_type::type>; }
    //Accessors to components
    template<size_t n>
    comp_type comp() const {
      if constexpr (!is_packed())
        return *(reinterpret_cast<const comp_type*>(&m_pix[n * sizeof(comp_type)]));
      else
      {
        const pack_type* pointer = reinterpret_cast<const pack_type*>(&m_pix);
        return pointer->template comp<n>();
      }
    }
    comp_type comp_i(size_t i) const {
      switch (i) {
      case 0:  return comp<0>();
      case 1:  
        if constexpr (NbComp<pf>::val > 1)
          return comp<1>();
        else
          throw std::runtime_error("You tried to access a pixel component that doesn't exist");
      case 2:  
        if constexpr (NbComp<pf>::val > 2)
          return comp<2>();
        else
          throw std::runtime_error("You tried to access a pixel component that doesn't exist");
      case 3:
        if constexpr (NbComp<pf>::val > 3)
          return comp<3>();
        else
          throw std::runtime_error("You tried to access a pixel component that doesn't exist");
      default: throw std::runtime_error("You tried to access a pixel component that doesn't exist");
      }
    }

  };



}