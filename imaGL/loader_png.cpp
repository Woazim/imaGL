#include "loader_png.h"
#ifdef _HAS_PNG

#include "privateimagldata.h"
#include <cstring>
#include <algorithm>
#ifdef __cpp_lib_endian
#include <bit>
#else
#include <type_traits>
#endif

namespace imaGL {

  void CLoaderPNG::png_read_fn(png_structp png_ptr, png_bytep data, size_t length)
  {
    std::istream& is = *static_cast<std::istream*>(png_get_io_ptr(png_ptr));
    is.read(reinterpret_cast<char*>(data), length);
    if (is.eof())
      throw std::runtime_error("Unexpected end of PNG data");
  }

  CPrivateImaGLData imaGL::CLoaderPNG::load(std::istream& is)
  {
    const size_t PNG_SIG_LENGTH = 8; //Must not exceed 8 (according to PNG spec)

    //First, test if this data is a png file
    //is.seekg(0, is.beg);
    char sig[PNG_SIG_LENGTH];
    is.read(sig, PNG_SIG_LENGTH);
    if (png_sig_cmp(reinterpret_cast<png_const_bytep>(sig), 0, PNG_SIG_LENGTH))
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

    CImaGL::EPixelFormat pf = CImaGL::EPixelFormat::Undefined;
    CImaGL::EPixelType pt = CImaGL::EPixelType::Undefined;

    switch (color_type)
    {
    case PNG_COLOR_TYPE_GRAY:
      pf = CImaGL::EPixelFormat::R;
      break;
    case PNG_COLOR_TYPE_GRAY_ALPHA:
      pf = CImaGL::EPixelFormat::RG;
      break;
    case PNG_COLOR_TYPE_PALETTE: //Colormap is an array of png_color (so it is 8-bit RGB pixels)
      pf = CImaGL::EPixelFormat::RGB;
      break;
    case PNG_COLOR_TYPE_RGB:
      pf = CImaGL::EPixelFormat::RGB;
      break;
    case PNG_COLOR_TYPE_RGB_ALPHA:
      pf = CImaGL::EPixelFormat::RGBA;
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
      //Since pixels will be expanded, they will be stored in 1 byte.
      pt = CImaGL::EPixelType::UByte;
      break;
    case 8:
      pt = CImaGL::EPixelType::UByte;
      break;
    case 16:
      pt = CImaGL::EPixelType::UShort;
      break;
    default:
      break;
    }

    if (bit_depth == 16 && std::endian::native == std::endian::little)  //Put bits in little-endian order
      png_set_swap(png_ptr);

    if (color_type == PNG_COLOR_TYPE_PALETTE) //Transform paletted images to RGB
      png_set_palette_to_rgb(png_ptr);

    if (png_get_valid(png_ptr, info_ptr, //adds a full alpha channel if there is transparency information in a tRNS chunk
      PNG_INFO_tRNS)) png_set_tRNS_to_alpha(png_ptr);

    if (color_type == PNG_COLOR_TYPE_GRAY && //transform less than 1-byte pixels to 1-byte
      bit_depth < 8) png_set_expand_gray_1_2_4_to_8(png_ptr);


    //Allocate memory for image
    CPrivateImaGLData ret(png_get_image_width(png_ptr, info_ptr), png_get_image_height(png_ptr, info_ptr), pf, pt);
    //Pointers to row starts
    std::vector<std::byte*> row_pointers;
    row_pointers.resize(ret.height());
    //Flip image since OpenGL expects texture to be read from bottom to top
    for (size_t i = 0; i < ret.height(); ++i)
      row_pointers[ret.height() - i - 1] = ret.data().data() + i * ret.width() * ret.pixelSize();
    //png_set_rows(png_ptr, info_ptr, row_pointers.data());

    //read the image
    png_read_image(png_ptr, reinterpret_cast<png_bytepp>(row_pointers.data()));

    png_read_end(png_ptr, nullptr); //Needed to put the read position of the stream at the end of PNG stream.

    //We must free memory, since we are gentlemen and ladies
    png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);

    return ret;
  }

}

#endif