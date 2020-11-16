/*****************************************************************//**
 * \file   imaGL.h
 * \brief  Main file of imaGL. You must include this file to use imaGL
 * 
 * Every thing is declared in imaGL namespace.
 * 
 * \author Benjamin ALBOUY-KISSI
 * \date   2020
 * \copyright LGPL v3
 *********************************************************************/
#pragma once

#include <vector>
#include <string_view>
#include <iostream>
#include <memory>
#include <map>
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

/**
 * \namespace imaGL
 * \brief All imaGL features are declared in this namespace.
 */
namespace imaGL {

  /**
   * \brief Macro to create function templates for function family map creation.
   * 
   * This macro creates two template functions called <em>name</em>_fnMap() and
   * <em>name</em>_fnMap_rec. The first one returns a std::map which associates 
   * pixel_type_id values to corresponding <em>name</em>\<Pixel\<CImaGL::EPixelFormat, CImaGL::EPixelType\>(...)
   * functions. The second one is used for recursivity creation from the first one.
   * For simplicity, none of these template should be used directly. Instead, use \ref create_fnMap
   * to simply create the map for whole function family.
   * 
   * \param function_template_name This is the name of the function family
   * 
   * \see create_fnMap
   */
#define _create_fnMap(function_template_name) \
  template<size_t i, unsigned int... pixel_type_ids> \
  void function_template_name##_fnMap_rec(std::map<unsigned int, decltype(function_template_name<Pixel<CImaGL::EPixelFormat::Undefined, CImaGL::EPixelType::Undefined>>)*>& fnMap) \
  { \
    if constexpr (i < sizeof...(pixel_type_ids)) { \
      constexpr unsigned int types[] = { pixel_type_ids... }; \
      constexpr unsigned int type = types[i]; \
      fnMap.insert({ type, function_template_name<Pixel<pixel_id_format<type>, pixel_id_type<type>>> }); \
      function_template_name##_fnMap_rec<i + 1, pixel_type_ids...>(fnMap); \
    } \
  } \
 \
  template<unsigned int... pixel_type_ids> \
  std::map<unsigned int, decltype(function_template_name<Pixel<CImaGL::EPixelFormat::Undefined, CImaGL::EPixelType::Undefined>>)*> function_template_name##_fnMap() { \
    std::map<unsigned int, decltype(function_template_name<Pixel<CImaGL::EPixelFormat::Undefined, CImaGL::EPixelType::Undefined>>)*> fnMap; \
    function_template_name##_fnMap_rec<0, pixel_type_ids...>(fnMap); \
    return fnMap; \
  }

  /**
   * \brief Macro that creates the function family map
   * 
   * This macro uses the previously declared thanks to \ref _create_fnMap template functions
   * to create a family function map.
   * You should use \ref _create_fnMap and \ref create_fnMap as in the following example.
   * 
   * The purpose of these two macros is to let you choose a templated function at runtime
   * when pixel type is not known.
   * 
   * In a declaration section of your files, declare a template function followed by a 
   * call to \ref _create_fnMap like this:
   * 
   * \snippet this template declaration of function family
   * 
   * Then, wherever you have to use this function family, just do like this:
   * 
   * \snippet imaGL.cpp use of a function family
   * 
   * \param function_template_name The name of the function family.
   * 
   * \see _create_fnMap
   */
#define create_fnMap(function_template_name) \
  function_template_name##_fnMap< \
    pixel_type_id<CImaGL::EPixelFormat::R, CImaGL::EPixelType::Byte>, \
    pixel_type_id<CImaGL::EPixelFormat::R, CImaGL::EPixelType::Float>, \
    /*pixel_type_id<CImaGL::EPixelFormat::R, CImaGL::EPixelType::HFloat>,*/ \
    pixel_type_id<CImaGL::EPixelFormat::R, CImaGL::EPixelType::Int>, \
    pixel_type_id<CImaGL::EPixelFormat::R, CImaGL::EPixelType::Short>, \
    pixel_type_id<CImaGL::EPixelFormat::R, CImaGL::EPixelType::UByte>, \
    pixel_type_id<CImaGL::EPixelFormat::R, CImaGL::EPixelType::UInt>, \
    pixel_type_id<CImaGL::EPixelFormat::R, CImaGL::EPixelType::UShort>, \
    pixel_type_id<CImaGL::EPixelFormat::RG, CImaGL::EPixelType::Byte>, \
    pixel_type_id<CImaGL::EPixelFormat::RG, CImaGL::EPixelType::Float>, \
    /*pixel_type_id<CImaGL::EPixelFormat::RG, CImaGL::EPixelType::HFloat>,*/ \
    pixel_type_id<CImaGL::EPixelFormat::RG, CImaGL::EPixelType::Int>, \
    pixel_type_id<CImaGL::EPixelFormat::RG, CImaGL::EPixelType::Short>, \
    pixel_type_id<CImaGL::EPixelFormat::RG, CImaGL::EPixelType::UByte>, \
    pixel_type_id<CImaGL::EPixelFormat::RG, CImaGL::EPixelType::UInt>, \
    pixel_type_id<CImaGL::EPixelFormat::RG, CImaGL::EPixelType::UShort>, \
    pixel_type_id<CImaGL::EPixelFormat::RGB, CImaGL::EPixelType::Byte>, \
    pixel_type_id<CImaGL::EPixelFormat::RGB, CImaGL::EPixelType::Float>, \
    /*pixel_type_id<CImaGL::EPixelFormat::RGB, CImaGL::EPixelType::HFloat>,*/ \
    pixel_type_id<CImaGL::EPixelFormat::RGB, CImaGL::EPixelType::Int>, \
    pixel_type_id<CImaGL::EPixelFormat::RGB, CImaGL::EPixelType::Short>, \
    pixel_type_id<CImaGL::EPixelFormat::RGB, CImaGL::EPixelType::UByte>, \
    pixel_type_id<CImaGL::EPixelFormat::RGB, CImaGL::EPixelType::UInt>, \
    pixel_type_id<CImaGL::EPixelFormat::RGB, CImaGL::EPixelType::UShort>, \
    pixel_type_id<CImaGL::EPixelFormat::BGR, CImaGL::EPixelType::Byte>, \
    pixel_type_id<CImaGL::EPixelFormat::BGR, CImaGL::EPixelType::Float>, \
    /*pixel_type_id<CImaGL::EPixelFormat::BGR, CImaGL::EPixelType::HFloat>,*/ \
    pixel_type_id<CImaGL::EPixelFormat::BGR, CImaGL::EPixelType::Int>, \
    pixel_type_id<CImaGL::EPixelFormat::BGR, CImaGL::EPixelType::Short>, \
    pixel_type_id<CImaGL::EPixelFormat::BGR, CImaGL::EPixelType::UByte>, \
    pixel_type_id<CImaGL::EPixelFormat::BGR, CImaGL::EPixelType::UInt>, \
    pixel_type_id<CImaGL::EPixelFormat::BGR, CImaGL::EPixelType::UShort>, \
    pixel_type_id<CImaGL::EPixelFormat::RGBA, CImaGL::EPixelType::Byte>, \
    pixel_type_id<CImaGL::EPixelFormat::RGBA, CImaGL::EPixelType::Float>, \
    /*pixel_type_id<CImaGL::EPixelFormat::RGBA, CImaGL::EPixelType::HFloat>,*/ \
    pixel_type_id<CImaGL::EPixelFormat::RGBA, CImaGL::EPixelType::Int>, \
    pixel_type_id<CImaGL::EPixelFormat::RGBA, CImaGL::EPixelType::Short>, \
    pixel_type_id<CImaGL::EPixelFormat::RGBA, CImaGL::EPixelType::UByte>, \
    pixel_type_id<CImaGL::EPixelFormat::RGBA, CImaGL::EPixelType::UInt>, \
    pixel_type_id<CImaGL::EPixelFormat::RGBA, CImaGL::EPixelType::UShort>, \
    pixel_type_id<CImaGL::EPixelFormat::BGRA, CImaGL::EPixelType::Byte>, \
    pixel_type_id<CImaGL::EPixelFormat::BGRA, CImaGL::EPixelType::Float>, \
    /*pixel_type_id<CImaGL::EPixelFormat::BGRA, CImaGL::EPixelType::HFloat>,*/ \
    pixel_type_id<CImaGL::EPixelFormat::BGRA, CImaGL::EPixelType::Int>, \
    pixel_type_id<CImaGL::EPixelFormat::BGRA, CImaGL::EPixelType::Short>, \
    pixel_type_id<CImaGL::EPixelFormat::BGRA, CImaGL::EPixelType::UByte>, \
    pixel_type_id<CImaGL::EPixelFormat::BGRA, CImaGL::EPixelType::UInt>, \
    pixel_type_id<CImaGL::EPixelFormat::BGRA, CImaGL::EPixelType::UShort>, \
    pixel_type_id<CImaGL::EPixelFormat::RGB, CImaGL::EPixelType::UByte_3_3_2>, \
    pixel_type_id<CImaGL::EPixelFormat::BGR, CImaGL::EPixelType::UByte_3_3_2>, \
    pixel_type_id<CImaGL::EPixelFormat::RGB, CImaGL::EPixelType::UByte_2_3_3_Rev>, \
    pixel_type_id<CImaGL::EPixelFormat::BGR, CImaGL::EPixelType::UByte_2_3_3_Rev>, \
    pixel_type_id<CImaGL::EPixelFormat::RGB, CImaGL::EPixelType::UShort_5_6_5>, \
    pixel_type_id<CImaGL::EPixelFormat::BGR, CImaGL::EPixelType::UShort_5_6_5>, \
    pixel_type_id<CImaGL::EPixelFormat::RGB, CImaGL::EPixelType::UShort_5_6_5_Rev>, \
    pixel_type_id<CImaGL::EPixelFormat::BGR, CImaGL::EPixelType::UShort_5_6_5_Rev>, \
    pixel_type_id<CImaGL::EPixelFormat::RGBA, CImaGL::EPixelType::UShort_4_4_4_4>, \
    pixel_type_id<CImaGL::EPixelFormat::BGRA, CImaGL::EPixelType::UShort_4_4_4_4>, \
    pixel_type_id<CImaGL::EPixelFormat::RGBA, CImaGL::EPixelType::UShort_4_4_4_4_Rev>, \
    pixel_type_id<CImaGL::EPixelFormat::BGRA, CImaGL::EPixelType::UShort_4_4_4_4_Rev>, \
    pixel_type_id<CImaGL::EPixelFormat::RGBA, CImaGL::EPixelType::UShort_5_5_5_1>, \
    pixel_type_id<CImaGL::EPixelFormat::BGRA, CImaGL::EPixelType::UShort_5_5_5_1>, \
    pixel_type_id<CImaGL::EPixelFormat::RGBA, CImaGL::EPixelType::UShort_1_5_5_5_Rev>, \
    pixel_type_id<CImaGL::EPixelFormat::BGRA, CImaGL::EPixelType::UShort_1_5_5_5_Rev>, \
    pixel_type_id<CImaGL::EPixelFormat::RGBA, CImaGL::EPixelType::UInt_8_8_8_8>, \
    pixel_type_id<CImaGL::EPixelFormat::BGRA, CImaGL::EPixelType::UInt_8_8_8_8>, \
    pixel_type_id<CImaGL::EPixelFormat::RGBA, CImaGL::EPixelType::UInt_8_8_8_8_Rev>, \
    pixel_type_id<CImaGL::EPixelFormat::BGRA, CImaGL::EPixelType::UInt_8_8_8_8_Rev>, \
    pixel_type_id<CImaGL::EPixelFormat::RGBA, CImaGL::EPixelType::UInt_10_10_10_2>, \
    pixel_type_id<CImaGL::EPixelFormat::BGRA, CImaGL::EPixelType::UInt_10_10_10_2>, \
    pixel_type_id<CImaGL::EPixelFormat::RGBA, CImaGL::EPixelType::UInt_2_10_10_10_Rev>, \
    pixel_type_id<CImaGL::EPixelFormat::BGRA, CImaGL::EPixelType::UInt_2_10_10_10_Rev> \
  >();

/** 
 * \brief Opaque pointer to private members. This help to export/import CImaGL class on dynamic linking.
 */
  struct SPrivateImaGLData;

  /**
   * \brief Describe image file format.
   * 
   * This class is used to express the image type when it cannot be determined from file name extension.
   * Typically, it is used when you want to load image data from memory.
   * 
   * You should create a CFileFormat according to the following supported file formats:
   * 
   * Needed preprocessor defines | file types | typeSig as char[4] / std::string          | typeSig as uint32_t (values depends on endianess of the architecture)
   * --------------------------- | ---------- | ----------------------------------------- | ---------------------------------------------------------------------
   * <em>none</em>               | all        | <tt>\"&nbsp;&nbsp;&nbsp;&nbsp;\"</tt>     | <tt>*reinterpret_cast<const uint32_t*>(\"&nbsp;&nbsp;&nbsp;&nbsp;\")</tt>
   * _HAS_PNG                    | png files  | <tt>"PNG "</tt>                           | <tt>*reinterpret_cast<const uint32_t*>("PNG ")</tt>
   *
   * \note A string literal suffix <tt>_FF</tt> is declared in imaGL::string_literals namespace to help you
   * create CFileFormat from a string. To use it, refers to the following example.
   *
   * \code{.cpp}
   * using namespace imaGL::string_literals;
   * imaGL::CFileFormat ff = "PNG "_FF;
   * \endcode
   * 
   * \note Special typeSig <tt>\"&nbsp;&nbsp;&nbsp;&nbsp;\"</tt> means that you don't know the file type.
   * In such a case, imaGL::CImaGL loader will try to guess file type from its data.
   *
   * \see CImaGL::CImaGL(std::istream&, CFileFormat)
   */
  class CFileFormat
  {
    uint32_t m_sig; //!< a 32-bit unsigned int that describes the format. The four bytes are the common file name extension.
  public:
    /**
     * \brief Construct a CFileFormat object from a common file name extension.
     * 
     * \param typeSig 4 characters that describe the file format
     * 
     * \see <a class="el" href="#details">CFileFormat detailed description</a> for a list of possible values.
     */
    explicit CFileFormat(const char typeSig[4]) {
      m_sig = *reinterpret_cast<const uint32_t*>(typeSig);
    }

    /**
     * \brief This constructor initialise the file format from a file magic number (uint32_t cast of typeSig).
     * 
     * \see <a class="el" href="#details">CFileFormat detailed description</a> for a list of possible values.
     */
    explicit CFileFormat(uint32_t typeSig) {
      m_sig = typeSig;
    }

    /**
     * \brief Convert this CFileFormat to a uint32_t typeSig
     * 
     * \see <a class="el" href="#details">CFileFormat detailed description</a> for a list of possible returned values.
     */
    explicit operator uint32_t() {
      return m_sig;
    }

    /**
     * \brief Convert this CFileFormat to a const char[4].
     * \note Exactly 4 chars must be accessed. It's not a null terminating string!
     * \see <a class="el" href="#details">CFileFormat detailed description</a> for a list of possible returned arrays.
     */
    explicit operator const char* (){
      return reinterpret_cast<const char*>(&m_sig);
    }

    /**
     * \brief Convert this CFileFormat to a std::string representation.
     * \see <a class="el" href="#details">CFileFormat detailed description</a> for a list of possible returned strings.
     */
    explicit operator ::std::string() {
      return ::std::string(static_cast<const char*>(*this), 4);
    }

#ifdef __cpp_impl_three_way_comparison
    /**
     * \brief CFileFormat must follow the Compare requirement to be useable as key in maps
     */
    std::strong_ordering operator<=>(const CFileFormat&) const = default;
#else
    ///@{
    /** CFileFormat must follow the Compare requirement to be useable as key in maps */
    bool operator<(const CFileFormat& ff) const { return m_sig < ff.m_sig; }
    bool operator>(const CFileFormat& ff) const { return m_sig > ff.m_sig; }
    bool operator==(const CFileFormat& ff) const { return m_sig == ff.m_sig; }
    ///@}
#endif
  };

  /**
   * \brief Contains imaGL defined string literal operators.
   */
  namespace string_literals {

    /**
     * \brief Create a CFileFormat from a string representation.
     * 
     * \param str String representation of the CFileFormat (ex: "PNG ")
     * \param length String length (must be 4)
     * 
     * \return A CFileFormat object corresonding to string representation
     */
    inline CFileFormat operator""_FF(const char* str, size_t length)
    {
      if (length != 4) {
        throw std::logic_error("You must use a string of 4 characters as CFileFormat signature");
      }
      return CFileFormat(str);
    }
  }

  /**
   * \defgroup exceptions Exception classes.
   * @{
   */

  /**
   * \brief Express a file that is not of the type it supposed to be.
   * 
   * For example, you tried to open a JPG file as a PNG one.
   * The message may help you.
   */
  class bad_format : public ::std::runtime_error {
  public:
    bad_format(const char* message) : ::std::runtime_error(message) {}
  };

  /**
   * \brief Express that no loader exists for a demanded file type.
   * 
   * The message may help you.
   */
  class loader_not_found : public ::std::runtime_error {
  public:
    loader_not_found(CFileFormat ff) :
      ::std::runtime_error("Loader for type " + static_cast<std::string>(ff) + " not found!")
    {}
  };

  /**
   * \brief No compatible loader has been found for an unknown file type.
   * 
   * When you try to open a file (from HD or memory) and you don't know the type, imaGL will try to find a compatible loader. If it doesn't succeed, this exception is thrown.
   * The message won't help you, but you can print it...
   */
  class compatible_loader_not_found : public ::std::runtime_error {
  public:
    compatible_loader_not_found() :
      ::std::runtime_error("Compatible loader has not been found!")
    {}
  };
  ///@}
  
  /**
   * \brief Main imaGL class. This is the class to use to load images.
   * 
   * \see \ref mainpage "Readme.md" for usage examples.
   */
  class IMAGL_API CImaGL
  {
  public:
    /**
     * \brief Pixel format enumeration
     * 
     * These values express pixel component format. By casting them to GLenum, they are
     * directly usable as <em>format</em> parameter of OpenGL's glTexImage* functions.
     * 
     * The following table list matches between this enum and OpenGL GLenum
     */
    enum class EPixelFormat : unsigned int
    {
      Undefined = 0,  //!< In your opinion? \emoji :wink:
      R     = 0x1903, //!< GL_RED
      RG    = 0x8227, //!< GL_RG
      RGB   = 0x1907, //!< GL_RGB
      BGR   = 0x80E0, //!< GL_BGR
      RGBA  = 0x1908, //!< GL_RGBA
      BGRA  = 0x80E1  //!< GL_BGRA
    };
    /**
     * \brief Pixel type enumeration
     *
     * These values express pixel component data type. By casting them to GLenum, they are
     * directly usable as <em>type</em> parameter of OpenGL's glTexImage* functions.
     * 
     * The following table list matches between this enum and OpenGL GLenum
     */
    enum class EPixelType : unsigned int
    {
      Undefined           = 0,      //!< In your opinion? \emoji :wink:
      UByte               = 0x1401, //!< GL_UNSIGNED_BYTE
      Byte                = 0x1400, //!< GL_BYTE
      UShort              = 0x1403, //!< GL_UNSIGNED_SHORT
      Short               = 0x1402, //!< GL_SHORT
      UInt                = 0x1405, //!< GL_UNSIGNED_INT
      Int                 = 0x1404, //!< GL_INT
      HFloat              = 0x140B, //!< GL_HALF_FLOAT
      Float               = 0x1406, //!< GL_FLOAT
      UByte_3_3_2         = 0x8032, //!< GL_UNSIGNED_BYTE_3_3_2
      UByte_2_3_3_Rev     = 0x8362, //!< GL_UNSIGNED_BYTE_2_3_3_REV
      UShort_5_6_5        = 0x8363, //!< GL_UNSIGNED_SHORT_5_6_5
      UShort_5_6_5_Rev    = 0x8364, //!< GL_UNSIGNED_SHORT_5_6_5_REV
      UShort_4_4_4_4      = 0x8033, //!< GL_UNSIGNED_SHORT_4_4_4_4
      UShort_4_4_4_4_Rev  = 0x8365, //!< GL_UNSIGNED_SHORT_4_4_4_4_REV
      UShort_5_5_5_1      = 0x8034, //!< GL_UNSIGNED_SHORT_5_5_5_1
      UShort_1_5_5_5_Rev  = 0x8366, //!< GL_UNSIGNED_SHORT_1_5_5_5_REV
      UInt_8_8_8_8        = 0x8035, //!< GL_UNSIGNED_INT_8_8_8_8
      UInt_8_8_8_8_Rev    = 0x8367, //!< GL_UNSIGNED_INT_8_8_8_8_REV
      UInt_10_10_10_2     = 0x8036, //!< GL_UNSIGNED_INT_10_10_10_2
      UInt_2_10_10_10_Rev = 0x8368  //!< GL_UNSIGNED_INT_2_10_10_10_REV
    };

  private:
    SPrivateImaGLData* m_pData; //!< Opaque pointer to private data

  public:
    /// \name Construction/Destruction
    /// @{
    /**
     * \brief Construct an imaGL::CImaGL by loading data from a file.
     * 
     * The object is created with pixel format and type choosen closest to file format by never loosing information.
     * 
     * \param filename File name in the file system.
     */
    CImaGL(std::string_view filename);
    /**
     * \brief Construct an imaGL::CImaGL by loading data from memory.
     *
     * The object is created with pixel format and type choosen closest to memory format by never loosing information.
     *
     * \param is An input stream object from which reading data.
     * \param format A CFileFormat to describe data format in \p is.
     * 
     * \note If \p format is not present, the special value <tt>\"&nbsp;&nbsp;&nbsp;&nbsp;\"_FF</tt> is used. It means that the format will be guessed from data.
     * 
     * \see imaGL::CFileFormat, operator""_FF in imaGL::string_literals
     */
    CImaGL(std::istream& is, CFileFormat format = CFileFormat("    "));

    /**
     * \brief Copy constructor.
     */
    CImaGL(const CImaGL& img);

    /**
     * \brief Move constructor.
     */
    CImaGL(CImaGL&& img) noexcept;

    /**
     * \brief Destructor.
     */
    ~CImaGL();

    /**
     * \brief Assignment operator.
     */
    CImaGL& operator=(const CImaGL& img);

    /**
     * \brief Move assignment operator.
     */
    CImaGL& operator=(CImaGL&& img) noexcept;
    ///@}

    ///\name Accessing information
    ///@{

    ///\brief Get pixel data in memory.
    ///\note Directly compatible with \p data parameter of OpenGL's glTexImage*
    const std::byte*      pixels()      const;
    ///\brief Get image width in pixels.
    ///\note Directly compatible with \p width parameter of OpenGL's glTexImage*
    size_t                width()       const;
    ///\brief Get image height in pixels.
    ///\note Directly compatible with \p height parameter of OpenGL's glTexImage*
    size_t                height()      const;
    ///\brief Get pixel format.
    ///\note Compatible with \p format parameter of OpenGL's glTexImage* after casting it to GLenum type
    EPixelFormat          pixelformat() const;
    ///\brief Get pixel type.
    ///\note Compatible with \p type parameter of OpenGL's glTexImage* after casting it to GLenum type
    EPixelType            pixeltype()   const;
    ///\brief Get pixel size in bytes.
    ///\note This can vary from 1 (ex: RGB / UByte_3_3_2) to 16 (ex: RGBA / UInt)
    size_t                pixelsize()   const;
    ///\brief Get the number of pixel components.
    ///\note =1 for R, =2 for RG, =3 for RGB / BGR, =4 for RGBA / BGRA
    size_t                nb_comp()     const;

    /**
     * \brief Direct access to a pixel component as a long long value.
     * 
     * \note You should ensure that pixel type is an integral type
     * 
     * \param row Row index of queried pixel in range [0, height())
     * \param col Colon index of queried pixel in range [0, width())
     * \param component Component index of queried pixel in range [0, nb_comp())
     */
    long long long_component_at(size_t row, size_t col, size_t component) const;
    /**
     * \brief Direct access to a pixel component as a float value.
     *
     * \note You should ensure that pixel type is a floating type
     *
     * \param row Row index of queried pixel in range [0, height())
     * \param col Colon index of queried pixel in range [0, width())
     * \param component Component index of queried pixel in range [0, nb_comp())
     */
    float     float_component_at(size_t row, size_t col, size_t component) const;
    ///@}

    ///\name Image manipulation
    ///@{
    /**
     * \brief Rescale the image.
     * 
     * Downscaling is done by running a mipmap reduction to get the nearest upper scale, 
     * then bilinear interpolation is used to compute sample pixel value.
     * 
     * Upscaling is directly done by bilinear interpolation
     * 
     * \param width New image width
     * \param height New image height
     */
    void rescale(size_t width, size_t height);

    /**
     * \brief Rescale the image to the nearest power of 2 size.
     *
     * The new size is computed as the next power of 2 of current size (width and height)
     * If the size is already a power of 2, nothing is done.
     */
    void rescaleToNextPowerOfTwo();
    ///@}
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
    using pixel_type = uint8_t;
    using comp_type = uint8_t;
    static const int nbComp = 3;
  };
  template<> struct Pack< CImaGL::EPixelType::UByte_2_3_3_Rev> {
    using pixel_type = uint8_t;
    using comp_type = uint8_t;
    static const int nbComp = 3;
  };
  template<> struct Pack< CImaGL::EPixelType::UShort_5_5_5_1> {
    using pixel_type = unsigned short;
    using comp_type = uint8_t;
    static const int nbComp = 4;
  };
  template<> struct Pack< CImaGL::EPixelType::UShort_1_5_5_5_Rev> {
    using pixel_type = unsigned short;
    using comp_type = uint8_t;
    static const int nbComp = 4;
  };
  template<> struct Pack< CImaGL::EPixelType::UShort_4_4_4_4> {
    using pixel_type = unsigned short;
    using comp_type = uint8_t;
    static const int nbComp = 4;
  };
  template<> struct Pack< CImaGL::EPixelType::UShort_4_4_4_4_Rev> {
    using pixel_type = unsigned short;
    using comp_type = uint8_t;
    static const int nbComp = 4;
  };
  template<> struct Pack< CImaGL::EPixelType::UShort_5_6_5> {
    using pixel_type = unsigned short;
    using comp_type = uint8_t;
    static const int nbComp = 3;
  };
  template<> struct Pack< CImaGL::EPixelType::UShort_5_6_5_Rev> {
    using pixel_type = unsigned short;
    using comp_type = uint8_t;
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
    using comp_type = uint8_t;
    static const int nbComp = 4;
  };
  template<> struct Pack< CImaGL::EPixelType::UInt_8_8_8_8_Rev> {
    using pixel_type = unsigned int;
    using comp_type = uint8_t;
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
    //Accessor to components for reading pixel
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
    //Accessor to component for writing to pixel
    template<size_t n>
    void comp(comp_type val) { static_assert(n < nb_comp, "The component indice is not valid!"); pixel |= componentMasks()[n]; pixel &= ((val << componentShifts()[n]) & componentMasks()[n]); }
    void comp_i(size_t i, comp_type val) {
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
  struct Comp { using type = void; using accum_type = void; };

  template<> struct Comp<CImaGL::EPixelFormat::R,     CImaGL::EPixelType::Byte> { using type = int8_t; using accum_type = short; };
  template<> struct Comp<CImaGL::EPixelFormat::RG,    CImaGL::EPixelType::Byte> { using type = int8_t; using accum_type = short; };
  template<> struct Comp<CImaGL::EPixelFormat::RGB,   CImaGL::EPixelType::Byte> { using type = int8_t; using accum_type = short; };
  template<> struct Comp<CImaGL::EPixelFormat::RGBA,  CImaGL::EPixelType::Byte> { using type = int8_t; using accum_type = short; };
  template<> struct Comp<CImaGL::EPixelFormat::BGR,   CImaGL::EPixelType::Byte> { using type = int8_t; using accum_type = short; };
  template<> struct Comp<CImaGL::EPixelFormat::BGRA,  CImaGL::EPixelType::Byte> { using type = int8_t; using accum_type = short; };

  template<> struct Comp<CImaGL::EPixelFormat::R,     CImaGL::EPixelType::Float> { using type = float; using accum_type = float; };
  template<> struct Comp<CImaGL::EPixelFormat::RG,    CImaGL::EPixelType::Float> { using type = float; using accum_type = float; };
  template<> struct Comp<CImaGL::EPixelFormat::RGB,   CImaGL::EPixelType::Float> { using type = float; using accum_type = float; };
  template<> struct Comp<CImaGL::EPixelFormat::RGBA,  CImaGL::EPixelType::Float> { using type = float; using accum_type = float; };
  template<> struct Comp<CImaGL::EPixelFormat::BGR,   CImaGL::EPixelType::Float> { using type = float; using accum_type = float; };
  template<> struct Comp<CImaGL::EPixelFormat::BGRA,  CImaGL::EPixelType::Float> { using type = float; using accum_type = float; };

  template<> struct Comp<CImaGL::EPixelFormat::R,     CImaGL::EPixelType::Int> { using type = int; using accum_type = long; };
  template<> struct Comp<CImaGL::EPixelFormat::RG,    CImaGL::EPixelType::Int> { using type = int; using accum_type = long; };
  template<> struct Comp<CImaGL::EPixelFormat::RGB,   CImaGL::EPixelType::Int> { using type = int; using accum_type = long; };
  template<> struct Comp<CImaGL::EPixelFormat::RGBA,  CImaGL::EPixelType::Int> { using type = int; using accum_type = long; };
  template<> struct Comp<CImaGL::EPixelFormat::BGR,   CImaGL::EPixelType::Int> { using type = int; using accum_type = long; };
  template<> struct Comp<CImaGL::EPixelFormat::BGRA,  CImaGL::EPixelType::Int> { using type = int; using accum_type = long; };

  template<> struct Comp<CImaGL::EPixelFormat::R,     CImaGL::EPixelType::Short> { using type = short; using accum_type = int; };
  template<> struct Comp<CImaGL::EPixelFormat::RG,    CImaGL::EPixelType::Short> { using type = short; using accum_type = int; };
  template<> struct Comp<CImaGL::EPixelFormat::RGB,   CImaGL::EPixelType::Short> { using type = short; using accum_type = int; };
  template<> struct Comp<CImaGL::EPixelFormat::RGBA,  CImaGL::EPixelType::Short> { using type = short; using accum_type = int; };
  template<> struct Comp<CImaGL::EPixelFormat::BGR,   CImaGL::EPixelType::Short> { using type = short; using accum_type = int; };
  template<> struct Comp<CImaGL::EPixelFormat::BGRA,  CImaGL::EPixelType::Short> { using type = short; using accum_type = int; };

  template<> struct Comp<CImaGL::EPixelFormat::R,     CImaGL::EPixelType::UByte> { using type = uint8_t; using accum_type = unsigned short; };
  template<> struct Comp<CImaGL::EPixelFormat::RG,    CImaGL::EPixelType::UByte> { using type = uint8_t; using accum_type = unsigned short; };
  template<> struct Comp<CImaGL::EPixelFormat::RGB,   CImaGL::EPixelType::UByte> { using type = uint8_t; using accum_type = unsigned short; };
  template<> struct Comp<CImaGL::EPixelFormat::RGBA,  CImaGL::EPixelType::UByte> { using type = uint8_t; using accum_type = unsigned short; };
  template<> struct Comp<CImaGL::EPixelFormat::BGR,   CImaGL::EPixelType::UByte> { using type = uint8_t; using accum_type = unsigned short; };
  template<> struct Comp<CImaGL::EPixelFormat::BGRA,  CImaGL::EPixelType::UByte> { using type = uint8_t; using accum_type = unsigned short; };

  template<> struct Comp<CImaGL::EPixelFormat::R,     CImaGL::EPixelType::UInt> { using type = unsigned int; using accum_type = unsigned long; };
  template<> struct Comp<CImaGL::EPixelFormat::RG,    CImaGL::EPixelType::UInt> { using type = unsigned int; using accum_type = unsigned long; };
  template<> struct Comp<CImaGL::EPixelFormat::RGB,   CImaGL::EPixelType::UInt> { using type = unsigned int; using accum_type = unsigned long; };
  template<> struct Comp<CImaGL::EPixelFormat::RGBA,  CImaGL::EPixelType::UInt> { using type = unsigned int; using accum_type = unsigned long; };
  template<> struct Comp<CImaGL::EPixelFormat::BGR,   CImaGL::EPixelType::UInt> { using type = unsigned int; using accum_type = unsigned long; };
  template<> struct Comp<CImaGL::EPixelFormat::BGRA,  CImaGL::EPixelType::UInt> { using type = unsigned int; using accum_type = unsigned long; };

  template<> struct Comp<CImaGL::EPixelFormat::R,     CImaGL::EPixelType::UShort> { using type = unsigned short; using accum_type = unsigned int; };
  template<> struct Comp<CImaGL::EPixelFormat::RG,    CImaGL::EPixelType::UShort> { using type = unsigned short; using accum_type = unsigned int; };
  template<> struct Comp<CImaGL::EPixelFormat::RGB,   CImaGL::EPixelType::UShort> { using type = unsigned short; using accum_type = unsigned int; };
  template<> struct Comp<CImaGL::EPixelFormat::RGBA,  CImaGL::EPixelType::UShort> { using type = unsigned short; using accum_type = unsigned int; };
  template<> struct Comp<CImaGL::EPixelFormat::BGR,   CImaGL::EPixelType::UShort> { using type = unsigned short; using accum_type = unsigned int; };
  template<> struct Comp<CImaGL::EPixelFormat::BGRA,  CImaGL::EPixelType::UShort> { using type = unsigned short; using accum_type = unsigned int; };

  template<> struct Comp<CImaGL::EPixelFormat::RGB, CImaGL::EPixelType::UByte_2_3_3_Rev> { using type = Pack<CImaGL::EPixelType::UByte_2_3_3_Rev>::comp_type; using accum_type = unsigned int; };
  template<> struct Comp<CImaGL::EPixelFormat::BGR, CImaGL::EPixelType::UByte_2_3_3_Rev> { using type = Pack<CImaGL::EPixelType::UByte_2_3_3_Rev>::comp_type; using accum_type = unsigned int; };

  template<> struct Comp<CImaGL::EPixelFormat::RGB, CImaGL::EPixelType::UByte_3_3_2> { using type = Pack<CImaGL::EPixelType::UByte_3_3_2>::comp_type; using accum_type = unsigned int; };
  template<> struct Comp<CImaGL::EPixelFormat::BGR, CImaGL::EPixelType::UByte_3_3_2> { using type = Pack<CImaGL::EPixelType::UByte_3_3_2>::comp_type; using accum_type = unsigned int; };

  template<> struct Comp<CImaGL::EPixelFormat::RGBA, CImaGL::EPixelType::UInt_10_10_10_2> { using type = Pack<CImaGL::EPixelType::UInt_10_10_10_2>::comp_type; using accum_type = unsigned long; };
  template<> struct Comp<CImaGL::EPixelFormat::BGRA, CImaGL::EPixelType::UInt_10_10_10_2> { using type = Pack<CImaGL::EPixelType::UInt_10_10_10_2>::comp_type; using accum_type = unsigned long; };

  template<> struct Comp<CImaGL::EPixelFormat::RGBA, CImaGL::EPixelType::UInt_2_10_10_10_Rev> { using type = Pack<CImaGL::EPixelType::UInt_2_10_10_10_Rev>::comp_type; using accum_type = unsigned long; };
  template<> struct Comp<CImaGL::EPixelFormat::BGRA, CImaGL::EPixelType::UInt_2_10_10_10_Rev> { using type = Pack<CImaGL::EPixelType::UInt_2_10_10_10_Rev>::comp_type; using accum_type = unsigned long; };

  template<> struct Comp<CImaGL::EPixelFormat::RGBA, CImaGL::EPixelType::UInt_8_8_8_8> { using type = Pack<CImaGL::EPixelType::UInt_8_8_8_8>::comp_type; using accum_type = unsigned long; };
  template<> struct Comp<CImaGL::EPixelFormat::BGRA, CImaGL::EPixelType::UInt_8_8_8_8> { using type = Pack<CImaGL::EPixelType::UInt_8_8_8_8>::comp_type; using accum_type = unsigned long; };

  template<> struct Comp<CImaGL::EPixelFormat::RGBA, CImaGL::EPixelType::UInt_8_8_8_8_Rev> { using type = Pack<CImaGL::EPixelType::UInt_8_8_8_8_Rev>::comp_type; using accum_type = unsigned long; };
  template<> struct Comp<CImaGL::EPixelFormat::BGRA, CImaGL::EPixelType::UInt_8_8_8_8_Rev> { using type = Pack<CImaGL::EPixelType::UInt_8_8_8_8_Rev>::comp_type; using accum_type = unsigned long; };

  template<> struct Comp<CImaGL::EPixelFormat::RGBA, CImaGL::EPixelType::UShort_1_5_5_5_Rev> { using type = Pack<CImaGL::EPixelType::UShort_1_5_5_5_Rev>::comp_type; using accum_type = unsigned int; };
  template<> struct Comp<CImaGL::EPixelFormat::BGRA, CImaGL::EPixelType::UShort_1_5_5_5_Rev> { using type = Pack<CImaGL::EPixelType::UShort_1_5_5_5_Rev>::comp_type; using accum_type = unsigned int; };

  template<> struct Comp<CImaGL::EPixelFormat::RGBA, CImaGL::EPixelType::UShort_4_4_4_4> { using type = Pack<CImaGL::EPixelType::UShort_4_4_4_4>::comp_type; using accum_type = unsigned int; };
  template<> struct Comp<CImaGL::EPixelFormat::BGRA, CImaGL::EPixelType::UShort_4_4_4_4> { using type = Pack<CImaGL::EPixelType::UShort_4_4_4_4>::comp_type; using accum_type = unsigned int; };

  template<> struct Comp<CImaGL::EPixelFormat::RGBA, CImaGL::EPixelType::UShort_4_4_4_4_Rev> { using type = Pack<CImaGL::EPixelType::UShort_4_4_4_4_Rev>::comp_type; using accum_type = unsigned int; };
  template<> struct Comp<CImaGL::EPixelFormat::BGRA, CImaGL::EPixelType::UShort_4_4_4_4_Rev> { using type = Pack<CImaGL::EPixelType::UShort_4_4_4_4_Rev>::comp_type; using accum_type = unsigned int; };

  template<> struct Comp<CImaGL::EPixelFormat::RGBA, CImaGL::EPixelType::UShort_5_5_5_1> { using type = Pack<CImaGL::EPixelType::UShort_5_5_5_1>::comp_type; using accum_type = unsigned int; };
  template<> struct Comp<CImaGL::EPixelFormat::BGRA, CImaGL::EPixelType::UShort_5_5_5_1> { using type = Pack<CImaGL::EPixelType::UShort_5_5_5_1>::comp_type; using accum_type = unsigned int; };

  template<> struct Comp<CImaGL::EPixelFormat::RGB, CImaGL::EPixelType::UShort_5_6_5> { using type = Pack<CImaGL::EPixelType::UShort_5_6_5>::comp_type; using accum_type = unsigned int; };
  template<> struct Comp<CImaGL::EPixelFormat::BGR, CImaGL::EPixelType::UShort_5_6_5> { using type = Pack<CImaGL::EPixelType::UShort_5_6_5>::comp_type; using accum_type = unsigned int; };

  template<> struct Comp<CImaGL::EPixelFormat::RGB, CImaGL::EPixelType::UShort_5_6_5_Rev> { using type = Pack<CImaGL::EPixelType::UShort_5_6_5_Rev>::comp_type; using accum_type = unsigned int; };
  template<> struct Comp<CImaGL::EPixelFormat::BGR, CImaGL::EPixelType::UShort_5_6_5_Rev> { using type = Pack<CImaGL::EPixelType::UShort_5_6_5_Rev>::comp_type; using accum_type = unsigned int; };

  template<CImaGL::EPixelFormat pf>
  struct NbComp { static const size_t val = 0; };

  template<> struct NbComp<CImaGL::EPixelFormat::R>    { static const size_t val = 1; };
  template<> struct NbComp<CImaGL::EPixelFormat::RG>   { static const size_t val = 2; };
  template<> struct NbComp<CImaGL::EPixelFormat::RGB>  { static const size_t val = 3; };
  template<> struct NbComp<CImaGL::EPixelFormat::BGR>  { static const size_t val = 3; };
  template<> struct NbComp<CImaGL::EPixelFormat::RGBA> { static const size_t val = 4; };
  template<> struct NbComp<CImaGL::EPixelFormat::BGRA> { static const size_t val = 4; };

  template<typename type, size_t nNbComp>
  class PixelAccumulator {
    type m_pix[nNbComp] = { 0 }; 
  public:

    template<size_t n>
    type comp() const { static_assert(n < nNbComp); return m_pix[n]; }

    template<typename pixel_type>
    PixelAccumulator& operator+=(const pixel_type& pix)
    {
      static_assert(nNbComp == NbComp<pixel_type::pixel_format()>::val);
      m_pix[0] += pix.template comp<0>();
      if constexpr (nNbComp > 1)
        m_pix[1] += pix.template comp<1>();
      if constexpr (nNbComp > 2)
        m_pix[2] += pix.template comp<2>();
      if constexpr (nNbComp > 3)
        m_pix[3] += pix.template comp<3>();
      return *this;
    }

    template<typename scalar>
    PixelAccumulator& operator/=(const scalar& val)
    {
      for (size_t i = 0; i < nNbComp; ++i)
        m_pix[i] = static_cast<type>(m_pix[i] / val);
      return *this;
    }

    template<typename scalar>
    PixelAccumulator& operator*=(const scalar& val)
    {
      for (size_t i = 0; i < nNbComp; ++i)
        m_pix[i] = static_cast<type>(m_pix[i] * val);
      return *this;
    }
  };

  template<CImaGL::EPixelFormat pf, CImaGL::EPixelType pt>
  constexpr unsigned int pixel_type_id = static_cast<unsigned int>(pf) << 16 | static_cast<unsigned int>(pt);
  template<unsigned int pid>
  constexpr CImaGL::EPixelFormat pixel_id_format = static_cast<CImaGL::EPixelFormat>(pid >> 16);
  template<unsigned int pid>
  constexpr CImaGL::EPixelType pixel_id_type = static_cast<CImaGL::EPixelType>(pid & 0xFFFF);

  inline unsigned int fn_pixel_type_id(CImaGL::EPixelFormat pf, CImaGL::EPixelType pt) { return static_cast<unsigned int>(pf) << 16 | static_cast<unsigned int>(pt); }

  template<CImaGL::EPixelFormat pf, CImaGL::EPixelType pt>
  class Pixel {
    class floatPixel {
      double m_pix[NbComp<pf>::val] = { 0.0 };
      friend class Pixel<pf, pt>;
    public:
      floatPixel operator+(const floatPixel& fp) const
      {
        floatPixel ret;
        ret.m_pix[0] = m_pix[0] + fp.m_pix[0];
        if constexpr (NbComp<pf>::val > 1)
          ret.m_pix[1] = m_pix[1] + fp.m_pix[1];
        if constexpr (NbComp<pf>::val > 2)
          ret.m_pix[2] = m_pix[2] + fp.m_pix[2];
        if constexpr (NbComp<pf>::val > 3)
          ret.m_pix[3] = m_pix[3] + fp.m_pix[3];
        return ret;
      }
    };
    static constexpr size_t pixelsize = computePixelSize(pf, pt);
    std::byte m_pix[pixelsize];
  public:
    //Type information about this class
    using comp_type = typename Comp<pf, pt>::type;
    using pack_type = PackedPixel<pt>;
    using accum_type = PixelAccumulator<typename Comp<pf, pt>::accum_type, NbComp<pf>::val>;
    //Static information about this class
    static constexpr CImaGL::EPixelFormat pixel_format() { return pf; }
    static constexpr CImaGL::EPixelType   pixel_type()   { return pt; }
    static constexpr size_t               pixel_size()   { return pixelsize; }
    static constexpr bool                 is_packed()    { return !std::is_pointer_v<typename pack_type::type>; }
    static constexpr unsigned int         type_id()      { return pixel_type_id<pf ,pt>; }
    static constexpr size_t               nb_comp()      { return NbComp<pf>::val; }

    Pixel& operator=(const accum_type& accumulator)
    {
      comp<0>(static_cast<comp_type>(accumulator.template comp<0>()));
      if constexpr (NbComp<pf>::val > 1)
        comp<1>(static_cast<comp_type>(accumulator.template comp<1>()));
      if constexpr (NbComp<pf>::val > 2)
        comp<2>(static_cast<comp_type>(accumulator.template comp<2>()));
      if constexpr (NbComp<pf>::val > 3)
        comp<3>(static_cast<comp_type>(accumulator.template comp<3>()));
      return *this;
    }

    Pixel& operator=(const floatPixel& fp)
    {
      comp<0>(static_cast<comp_type>(fp.m_pix[0]));
      if constexpr (NbComp<pf>::val > 1)
        comp<1>(static_cast<comp_type>(fp.m_pix[1]));
      if constexpr (NbComp<pf>::val > 2)
        comp<2>(static_cast<comp_type>(fp.m_pix[2]));
      if constexpr (NbComp<pf>::val > 3)
        comp<3>(static_cast<comp_type>(fp.m_pix[3]));
      return *this;
    }

    floatPixel operator*(double scalar) const
    {
      floatPixel ret;
      ret.m_pix[0] = comp<0>() * scalar;
      if constexpr (NbComp<pf>::val > 1)
        ret.m_pix[1] = comp<1>() * scalar;
      if constexpr (NbComp<pf>::val > 2)
        ret.m_pix[2] = comp<2>() * scalar;
      if constexpr (NbComp<pf>::val > 3)
        ret.m_pix[3] = comp<3>() * scalar;
      return ret;
    }
#ifdef __cpp_impl_three_way_comparison
    bool operator==(const Pixel& pix) const = default;
#else
    bool operator==(const Pixel& pix) const
    {
      for (size_t i = 0; i < pixelsize; ++i)
        if (m_pix[i] != pix.m_pix[i])
          return false;
      return true;
    }
    bool operator!=(const Pixel& pix) const
    {
      return !(*this == pix);
    }
#endif // __cpp_impl_three_way_comparison

    //Accessors to components
    //For reading pixel
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
    //For writing to pixel
    template<size_t n>
    void comp(comp_type val) {
      if constexpr (!is_packed())
        *(reinterpret_cast<comp_type*>(&m_pix[n * sizeof(comp_type)])) = val;
      else
      {
        pack_type* pointer = reinterpret_cast<pack_type*>(&m_pix);
        pointer->template comp<n>(val);
      }
    }
    void comp_i(size_t i, comp_type val) {
      switch (i) {
      case 0: 
        comp<0>(val); 
        return;
      case 1:
        if constexpr (NbComp<pf>::val > 1)
        {
          comp<1>(val);
          return;
        }
        else
          throw std::runtime_error("You tried to access a pixel component that doesn't exist");
      case 2:
        if constexpr (NbComp<pf>::val > 2)
        {
          comp<2>(val);
          return;
        }
        else
          throw std::runtime_error("You tried to access a pixel component that doesn't exist");
      case 3:
        if constexpr (NbComp<pf>::val > 3)
        {
          comp<3>(val);
          return;
        }
        else
          throw std::runtime_error("You tried to access a pixel component that doesn't exist");
      default: throw std::runtime_error("You tried to access a pixel component that doesn't exist");
      }
    }

  };

  //![template declaration of function family]
  template<typename PixelType>
  size_t t_nb_comp()
  {
    return NbComp<PixelType::pixel_format()>::val;
  }
  _create_fnMap(t_nb_comp);
  //![template declaration of function family]

  template<CImaGL::EPixelFormat pf, CImaGL::EPixelType pt>
  std::ostream& operator<<(std::ostream& out, const Pixel<pf, pt>& pix)
  {
    if constexpr (sizeof(typename Pixel<pf, pt>::comp_type) == 1) // This is a char or unsigned char -> cast it to short to avoid to print character
    {
      out << static_cast<short>(pix.template comp<0>());
      if constexpr (Pixel<pf, pt>::nb_comp() > 1)
        out << " " << static_cast<short>(pix.template comp<1>());
      if constexpr (Pixel<pf, pt>::nb_comp() > 2)
        out << " " << static_cast<short>(pix.template comp<2>());
      if constexpr (Pixel<pf, pt>::nb_comp() > 3)
        out << " " << static_cast<short>(pix.template comp<3>());
    }
    else 
    {
      out << " " << pix.template comp<0>();
      if constexpr (Pixel<pf, pt>::nb_comp() > 1)
        out << " " << pix.template comp<1>();
      if constexpr (Pixel<pf, pt>::nb_comp() > 2)
        out << " " << pix.template comp<2>();
      if constexpr (Pixel<pf, pt>::nb_comp() > 3)
        out << " " << pix.template comp<3>();
    }
    return out;
  }
}