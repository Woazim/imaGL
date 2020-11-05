// imaGL.cpp : Définit les fonctions de la bibliothèque statique.
//

#include "imaGL.h"
#include "privateimagldata.h"
#include "loader_factory.h"
#include <algorithm>
#include <fstream>
#include <cassert>

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

  void CImaGL::upscale_x(const SPrivateImaGLData& source, SPrivateImaGLData& dest)
  {
  }


  //A passer en template dans un autre scale.h
  //templeter par le type de pixel
  //type de pixe à déterminer dans rescale()
  void CImaGL::downscale_x_by2(const SPrivateImaGLData& source, SPrivateImaGLData& dest)
  {
    dest.m_nHeight = source.m_nHeight;
    dest.m_nWidth = source.m_nWidth / 2;
    dest.m_PixelFormat = source.m_PixelFormat;
    dest.m_PixelType = source.m_PixelType;
    dest.m_nPixelSize = source.m_nPixelSize;
    dest.m_vRawData.resize(dest.m_nHeight * dest.m_nWidth * dest.m_nPixelSize);

    //for (size_t row = 0; row < dest.m_nHeight; ++row)
    //  for (size_t col = 0; col < dest.m_nWidth; ++col)
    //  {
    //    dest.m_vRawData[]
    //  }
  }

  void CImaGL::upscale_y(const SPrivateImaGLData& source, SPrivateImaGLData& dest)
  {
  }

  void CImaGL::downscale_y(const SPrivateImaGLData& source, SPrivateImaGLData& dest)
  {
  }

  void CImaGL::computePixelSize()
  {
    m_pData->m_nPixelSize = ImaGL::computePixelSize(m_pData->m_PixelFormat, m_pData->m_PixelType);
  }

  const unsigned char* CImaGL::pixels()      const { return m_pData->m_vRawData.data(); }
  size_t               CImaGL::width()       const { return m_pData->m_nWidth; }
  size_t               CImaGL::height()      const { return m_pData->m_nHeight; }
  CImaGL::EPixelFormat CImaGL::pixelformat() const { return m_pData->m_PixelFormat; }
  CImaGL::EPixelType   CImaGL::pixeltype()   const { return m_pData->m_PixelType; }
  size_t               CImaGL::pixelsize()   const { return m_pData->m_nPixelSize; }

  void CImaGL::rescale(int width, int height)
  {
    const size_t lastHeight = m_pData->m_nHeight;

    //First, rescale image along x
    SPrivateImaGLData tempImg;
    tempImg.m_nHeight = m_pData->m_nHeight;
    tempImg.m_nWidth = width;
    tempImg.m_PixelFormat = m_pData->m_PixelFormat;
    tempImg.m_PixelType = m_pData->m_PixelType;
    tempImg.m_nPixelSize = m_pData->m_nPixelSize;
    tempImg.m_vRawData.resize(tempImg.m_nWidth * tempImg.m_nHeight * tempImg.m_nPixelSize);

    //if (width > m_pData->m_nWidth)
    //  upscale_x(m_pData, tempImg);
    //else if (width < m_pData->m_nWidth)
    //  downscale_x(m_pData, tempImg);
    //else
    //  tempImg = *m_pData;

    //Then, rescale image along y
    m_pData->m_nHeight = height;
    m_pData->m_nWidth = width;
    m_pData->m_vRawData.resize(width * height * m_pData->m_nPixelSize);

    //if (height > lastHeight)
    //  upscale_y(tempImg, m_pData);
    //else if (width < lastHeight)
    //  downscale_y(tempImg, m_pData);
    //else
    //  *m_pData = tempImg;
  }

}