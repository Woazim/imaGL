// imaGL.cpp : Définit les fonctions de la bibliothèque statique.
//

#include "imaGL.h"
#include "privateimagldata.h"
#include "loader_factory.h"
#include <algorithm>
#include <fstream>

namespace ImaGL {

  CImaGL::CImaGL(std::string_view filename)
    : m_pData(new SPrivateImaGLData)
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
    
    computePixelSize();
  }

  CImaGL::CImaGL(std::istream& is, CFileFormat formatSig)
  {
    if(!is.good())
      throw std::runtime_error("Invalid stream");

    *m_pData = CLoaderFactory::getLoader(formatSig).load(is);

    computePixelSize();
  }

  CImaGL::~CImaGL()
  {
    delete m_pData;
  }

  void CImaGL::computePixelSize()
  {
    int nNbComp = 0;
    switch (m_pData->m_PixelFormat)
    {
    default:
    case CImaGL::EPixelFormat::Undefined:
      m_nPixelSize = 0;
      break;
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
    switch (m_pData->m_PixelType)
    {
    default:
    case CImaGL::EPixelType::Undefined:
      m_nPixelSize = 0;
      break;
    case CImaGL::EPixelType::UByte:
    case CImaGL::EPixelType::Byte:
      m_nPixelSize = nNbComp;
      break;
    case CImaGL::EPixelType::UShort:
    case CImaGL::EPixelType::Short:
      m_nPixelSize = nNbComp * 2;
      break;
    case CImaGL::EPixelType::UInt:
    case CImaGL::EPixelType::Int:
      m_nPixelSize = nNbComp * 4;
      break;
    case CImaGL::EPixelType::HFloat:
      m_nPixelSize = nNbComp * 2;
      break;
    case CImaGL::EPixelType::Float:
      m_nPixelSize = nNbComp * 4;
      break;
    case CImaGL::EPixelType::UByte_3_3_2:
    case CImaGL::EPixelType::UByte_2_3_3_Rev:
      m_nPixelSize = 1;
      break;
    case CImaGL::EPixelType::UShort_5_6_5:
    case CImaGL::EPixelType::UShort_5_6_5_Rev:
      m_nPixelSize = 2;
      break;
    case CImaGL::EPixelType::UShort_4_4_4_4:
    case CImaGL::EPixelType::UShort_4_4_4_4_Rev:
    case CImaGL::EPixelType::UShort_5_5_5_1:
    case CImaGL::EPixelType::UShort_1_5_5_5_Rev:
    case CImaGL::EPixelType::UInt_8_8_8_8:
    case CImaGL::EPixelType::UInt_8_8_8_8_Rev:
    case CImaGL::EPixelType::UInt_10_10_10_2:
    case CImaGL::EPixelType::UInt_2_10_10_10_Rev:
      m_nPixelSize = 4;
      break;
    }
  }

  const unsigned char* CImaGL::pixels()      const { return m_pData->m_vRawData.data(); }
  size_t               CImaGL::width()       const { return m_pData->m_nWidth; }
  size_t               CImaGL::height()      const { return m_pData->m_nHeight; }
  CImaGL::EPixelFormat CImaGL::pixelformat() const { return m_pData->m_PixelFormat; }
  CImaGL::EPixelType   CImaGL::pixeltype()   const { return m_pData->m_PixelType; }
  size_t               CImaGL::pixelsize()   const { return m_nPixelSize; }

}