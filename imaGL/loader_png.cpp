#include "loader_png.h"
#ifdef _HAS_LIBPNG

#include "privateimagldata.h"
#include <png.h>

namespace ImaGL {

  SPrivateImaGLData ImaGL::CLoaderPNG::load(std::istream& is)
  {
    png_image image;

    /* Only the image structure version number needs to be set. */
    memset(&image, 0, sizeof image);
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
      /* Change this to try different formats!  If you set a colormap format
       * then you must also supply a colormap below.
       */
      image.format = PNG_FORMAT_RGBA;

      std::vector<png_byte> pixels_buf(PNG_IMAGE_SIZE(image));

      if (!pixels_buf.empty())
      {
        if (png_image_finish_read(&image, NULL/*background*/, pixels_buf.data(),
          0/*row_stride*/, NULL/*colormap for PNG_FORMAT_FLAG_COLORMAP */))
        {
          SPrivateImaGLData ret;
          ret.m_vRawData = std::move(pixels_buf);
          ret.m_PixelFormat = CImaGL::EPixelFormat::RGBA;
          ret.m_PixelType = CImaGL::EPixelType::UByte;
          ret.m_nHeight = image.height;
          ret.m_nWidth = image.width;
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

  }

}

#endif