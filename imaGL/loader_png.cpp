#include "loader_png.h"
#ifdef _HAS_PNG

#include "privateimagldata.h"
#include <cstring>
#include <algorithm>

namespace ImaGL {
  void CLoaderPNG::getPixelFormatAndType(std::istream& is)
  {
    const size_t PNG_SIG_LENGTH = 8; //Must not exceed 8 (according to PNG spec)

    //First, test if this data is a png file
    is.seekg(0, is.beg);
    char sig[PNG_SIG_LENGTH];
    is.read(sig, PNG_SIG_LENGTH);
    if (png_sig_cmp(reinterpret_cast<unsigned char*>(sig), 0, PNG_SIG_LENGTH))
      throw bad_format("This data is not a PNG file");

    //Create png_struct / png_info
    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png_ptr)
      throw std::runtime_error("Unable to create a reading structure for a PNG");

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr)
    {
      png_destroy_read_struct(&png_ptr, nullptr, nullptr);
      throw std::runtime_error("Unable to create an info structure for a PNG");
    }

    png_set_read_fn(png_ptr, &is, png_read_fn);

    //And now, we can read png info header
    png_set_sig_bytes(png_ptr, PNG_SIG_LENGTH);
    png_read_info(png_ptr, info_ptr);
    int bit_depth, color_type;
    bit_depth = png_get_bit_depth(png_ptr, info_ptr);
    color_type = png_get_color_type(png_ptr, info_ptr);
    switch (color_type)
    {
    case PNG_COLOR_TYPE_GRAY:
      m_pf = CImaGL::EPixelFormat::R;
      break;
    case PNG_COLOR_TYPE_GRAY_ALPHA:
      m_pf = CImaGL::EPixelFormat::RG;
      break;
    case PNG_COLOR_TYPE_PALETTE: //Paletted image are more difficult to deal with. So we set it to RGBA.
      m_pf = CImaGL::EPixelFormat::RGBA;
      break;
    case PNG_COLOR_TYPE_RGB:
      m_pf = CImaGL::EPixelFormat::RGB;
      break;
    case PNG_COLOR_TYPE_RGB_ALPHA:
      m_pf = CImaGL::EPixelFormat::RGBA;
      break;
    default:
      break;
    }
    switch (bit_depth)
    {
    case 1:
    case 2:
    case 4:
      //It can be only PNG_COLOR_TYPE_GRAY or PNG_COLOR_TYPE_PALETTE
      if (m_pf == CImaGL::EPixelFormat::R)
        m_pt = CImaGL::EPixelType::UByte;
      else
        m_pt = CImaGL::EPixelType::UShort;
      break;
    case 8:
      m_pt = CImaGL::EPixelType::UByte;
      break;
    case 16:
      m_pt = CImaGL::EPixelType::UShort;
      break;
    default:
      break;
    }

    //We must free memory, since we are gentlemen and ladies
    png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
  }

  void CLoaderPNG::png_read_fn(png_structp png_ptr, png_bytep data, size_t length)
  {
    std::istream& is = *static_cast<std::istream*>(png_get_io_ptr(png_ptr));
    is.read(reinterpret_cast<char*>(data), length);
    if (is.eof())
      throw std::runtime_error("Unexpected end of PNG data");
  }

  SPrivateImaGLData ImaGL::CLoaderPNG::load(std::istream& is)
  {
    getPixelFormatAndType(is);

    png_image image;

    /* Only the image structure version number needs to be set. */
    std::memset(&image, 0, sizeof image);
    image.version = PNG_IMAGE_VERSION;

    //Goes to the end of the stream
    is.seekg(0, is.end);
    //Tell me where you are, it's your length
    const ::std::streampos nLength = is.tellg();
    //Go back to the beginning
    is.seekg(0, is.beg);

    //Allocate memory
    std::vector<png_byte> png_buf(nLength);
    //Read PNG memory to the buffer
    is.read(reinterpret_cast<char*>(png_buf.data()), nLength);

    if (png_image_begin_read_from_memory(&image, png_buf.data(), nLength))
    {
      switch (m_pf)
      {
      case CImaGL::EPixelFormat::R:
        image.format = PNG_FORMAT_GRAY;
        break;
      case CImaGL::EPixelFormat::RG:
        image.format = PNG_FORMAT_GA;
        break;
      case CImaGL::EPixelFormat::RGB:
        image.format = PNG_FORMAT_RGB;
        break;
      case CImaGL::EPixelFormat::RGBA:
        image.format = PNG_FORMAT_RGBA;
        break;
      default:
        break;
      }
      if (m_pt == CImaGL::EPixelType::UShort)
        image.format |= PNG_FORMAT_FLAG_LINEAR;

      std::vector<png_byte> pixels_buf(PNG_IMAGE_SIZE(image));

      if (!pixels_buf.empty())
      {
        if (png_image_finish_read(&image, NULL/*background*/, pixels_buf.data(),
          0/*row_stride*/, NULL/*colormap for PNG_FORMAT_FLAG_COLORMAP */))
        {
          SPrivateImaGLData ret;
          ret.m_vRawData = std::move(pixels_buf);
          ret.m_PixelFormat = m_pf;
          ret.m_PixelType = m_pt;
          ret.m_nHeight = image.height;
          ret.m_nWidth = image.width;
          //In case of 16-bit image, R, G and B are premultiplied by Alpha. So we need to reset initial components.
          //It doesn't work. I think there is no other solution: we must use libpng low level API.
          if (m_pt == CImaGL::EPixelType::UShort)
          {
            if (m_pf == CImaGL::EPixelFormat::RG)
            {
              Pixel2Comp<unsigned short>* pBeginPixel = reinterpret_cast<Pixel2Comp<unsigned short>*>(ret.m_vRawData.data());
              Pixel2Comp<unsigned short>* pEndPixel = pBeginPixel + ret.m_nHeight * ret.m_nWidth;
              std::for_each(pBeginPixel, pEndPixel, [](Pixel2Comp<unsigned short>& pixel) {
                if(pixel.comp2 != 0)
                  pixel.comp1 = (pixel.comp1 << 16) / pixel.comp2;
                });
            }
            if (m_pf == CImaGL::EPixelFormat::RGBA)
            {
              Pixel4Comp<unsigned short>* pBeginPixel = reinterpret_cast<Pixel4Comp<unsigned short>*>(ret.m_vRawData.data());
              Pixel4Comp<unsigned short>* pEndPixel = pBeginPixel + ret.m_nHeight * ret.m_nWidth;
              std::for_each(pBeginPixel, pEndPixel, [](Pixel4Comp<unsigned short>& pixel) {
                if (pixel.comp4 != 0)
                {
                  pixel.comp1 = (pixel.comp1 << 16) / pixel.comp4;
                  pixel.comp2 = (pixel.comp2 << 16) / pixel.comp4;
                  pixel.comp3 = (pixel.comp3 << 16) / pixel.comp4;
                }
                });
            }
          }
          return ret;
        }
        else
          throw std::runtime_error(image.message);
      }

      else
      {
        throw std::bad_alloc();

        /* This is the only place where a 'free' is required; libpng does
         * the cleanup on error and success, but in this case we couldn't
         * complete the read because of running out of memory and so libpng
         * has not got to the point where it can do cleanup.
         */
        png_image_free(&image);
      }
    }
    else
      /* Failed to read the first argument: */
      throw bad_format(image.message);

    return {};
  }

}

#endif