// imaGL.cpp : Définit les fonctions de la bibliothèque statique.
//

#include "public/imaGL/imaGL.h"
#include "privateimagldata.h"
#include "loader_factory.h"
#include <algorithm>
#include <fstream>
#include <cassert>
#include "rescale.h"

namespace imaGL {

  _create_fnMap(t_long_component_at);
  _create_fnMap(t_float_component_at);

  CImaGL::CImaGL(std::string_view filename)
    : m_pData(new CPrivateImaGLData)
  {
    std::ifstream is(std::string(filename), std::ios_base::in | std::ios_base::binary);
    if (!is.is_open())
      throw std::runtime_error("Unable to open file: " + std::string(filename));

    //First, get file extension
    std::string strExt;
    auto pos = filename.rfind('.');
    if (pos != filename.npos)
      strExt = filename.substr(pos + 1, 4);

    //In function of this, choose the right loader, then load file
    std::transform(strExt.begin(), strExt.end(), strExt.begin(), ::toupper);
    strExt += std::string(4 - strExt.length(), ' ');
    *m_pData = CLoaderFactory::getLoader(CFileFormat(strExt.c_str())).load(is);
  }

  CImaGL::CImaGL(std::istream& is, CFileFormat formatSig)
    : m_pData(new CPrivateImaGLData)
  {
    if(!is.good())
      throw std::runtime_error("Invalid stream");

    *m_pData = CLoaderFactory::getLoader(formatSig).load(is);
  }

  CImaGL::CImaGL(const CImaGL& img)
    : m_pData(new CPrivateImaGLData)
  {
    *m_pData = *img.m_pData;
  }

  CImaGL::CImaGL(CImaGL&& img) noexcept
  {
    m_pData = img.m_pData;
    img.m_pData = nullptr;
  }

  CImaGL::~CImaGL()
  {
    delete m_pData;
  }

  CImaGL& CImaGL::operator=(const CImaGL& img)
  {
    if (this == &img)
      return *this;

    if (!m_pData)
      m_pData = new CPrivateImaGLData;
    *m_pData = *img.m_pData;

    return *this;
  }

  CImaGL& CImaGL::operator=(CImaGL&& img) noexcept
  {
    if (this == &img)
      return *this;
    delete m_pData;
    m_pData = img.m_pData;
    img.m_pData = nullptr;
    return *this;
  }

  const std::byte*     CImaGL::pixels()      const { return m_pData ? m_pData->data().data() : nullptr; }
  std::int32_t         CImaGL::width()       const { return m_pData ? m_pData->width() : 0; }
  std::int32_t         CImaGL::height()      const { return m_pData ? m_pData->height() : 0; }
  CImaGL::EPixelFormat CImaGL::pixelformat() const { return m_pData ? m_pData->pixelFormat() : EPixelFormat::Undefined; }
  CImaGL::EPixelType   CImaGL::pixeltype()   const { return m_pData ? m_pData->pixelType() : EPixelType::Undefined; }
  size_t               CImaGL::pixelsize()   const { return m_pData ? m_pData->pixelSize() : 0; }

  //Comments are here to explain the example included in documentation
  //! [use of a function family]
  size_t CImaGL::nb_comp() const
  {
    //m_pData is a pointer to the opaque CPrivateImaGLData
    //It contains m_PixelFormat and m_PixelType members which respectly are 
    //the CImaGL::EPixelFormat and CImaGL::EPixelType values of the pixels 
    //stored in the CImaGL object.
    if (!m_pData) return 0;

    //fnMap is set static to be initialised only at the first run; create_fnMap create a std::map with 72 items.
    static auto fnMap = create_fnMap(t_nb_comp);

    //The created map associates pixel_type_id values to corresponding realisation 
    //of the t_nb_comp template.
    //Here fn_pixel_type_id helper function is used to compute pixel_type_id from 
    //CImaGL::EPixelFormat and CImaGL::EPixelType values.
    return fnMap[fn_pixel_type_id(m_pData->pixelFormat(), m_pData->pixelType())]();
  }
  //! [use of a function family]

  long long CImaGL::long_component_at(size_t row, size_t col, size_t component) const
  {
    if (!m_pData) return 0;
    static auto fnMap = create_fnMap(t_long_component_at);
    return fnMap[fn_pixel_type_id(m_pData->pixelFormat(), m_pData->pixelType())](*m_pData, row, col, component);
  }

  float CImaGL::float_component_at(size_t row, size_t col, size_t component) const
  {
    if (!m_pData) return 0;
    static auto fnMap = create_fnMap(t_float_component_at);
    return fnMap[fn_pixel_type_id(m_pData->pixelFormat(), m_pData->pixelType())](*m_pData, row, col, component);
  }

  void CImaGL::rescale(std::int32_t width, std::int32_t height)
  {
    if (!m_pData) return;
    const std::int32_t lastHeight = m_pData->height();

    //First, rescale image along x
    CPrivateImaGLData tempImg(width, m_pData->height(), m_pData->pixelFormat(), m_pData->pixelType());

    if (width > m_pData->width())
    {
      upscale_x(*m_pData, tempImg);
    }
    else if (width < m_pData->width())
    {
      downscale_x(*m_pData, tempImg);
    }
    else
      tempImg = *m_pData;

    //Then, rescale image along y
    *m_pData = CPrivateImaGLData(width, height, m_pData->pixelFormat(), m_pData->pixelType());

    if (height > lastHeight)
    {
      upscale_y(tempImg, *m_pData);
    }
    else if (height < lastHeight)
    {
      downscale_y(tempImg, *m_pData);
    }
    else
      *m_pData = std::move(tempImg);
  }

  void CImaGL::rescaleToNextPowerOfTwo()
  {
    //When c++20 will be here, we could use std::bit_ceil here
    //I propose here my own implementation
#if __cpp_lib_int_pow2 == 202002L
    using std::bit_ceil;
#endif // __cpp_lib_int_pow2
    rescale(bit_ceil(static_cast<std::uint32_t>(width())), bit_ceil(static_cast<std::uint32_t>(height())));
  }

}