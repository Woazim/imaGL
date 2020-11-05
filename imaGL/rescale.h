#pragma once

namespace ImaGL {

  template<typename PixelType>
  void CImaGL::downscale_x(const SPrivateImaGLData& source, SPrivateImaGLData& dest)
  {
    assert(source.m_nWidth > dest.m_nWidth);
    assert(source.m_nHeight == dest.m_nHeight);
    assert(dest.m_vRawData.size() == dest.m_nHeight * dest.m_nWidth * dest.m_nPixelSize);
    assert(source.m_vRawData.size() == source.m_nHeight * source.m_nWidth * source.m_nPixelSize);

    const double dInvScaleFactor = source.m_nWidth / (double)dest.m_nWidth;
    const size_t nInvScaleFactor = (size_t)dInvScaleFactor; //get integer part
    size_t nPrevPowerOf2 = 0;
    for (size_t nMask = (((size_t)1) << (sizeof(size_t) * 8 - 1));
      nPrevPowerOf2 == 0 && nMask != 0;
      nMask >>= 1
      )
    {
      nPrevPowerOf2 = nInvScaleFactor & nMask;
    }

    const double dFractInvScaleFactor = dInvScaleFactor - nInvScaleFactor; //get decimal part

    for (size_t row = 0; row < dest.m_nHeight; ++row)
      for (size_t destCol = 0; destCol < dest.m_nWidth; ++destCol)
      {
        //srcCol = destCol * dInvScaleFactor = destCol * nInvScaleFactor + destCol * dFractInvScaleFactor
        size_t srcCol = destCol * nInvScaleFactor;


      }

  }

}