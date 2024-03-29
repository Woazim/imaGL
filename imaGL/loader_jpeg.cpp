#include "loader_jpeg.h"
#ifdef _HAS_JPEG

#include "privateimagldata.h"
#include <cstring>
#include <algorithm>
#ifdef __cpp_lib_endian
#include <bit>
#else
#include <type_traits>
#endif
#include <vector>

namespace imaGL {

  CPrivateImaGLData imaGL::CLoaderJPEG::load(std::istream& is)
  {
    //Create jpeg decompressor and error handler
    jpeg_decompress_struct cinfo;
    my_error_mgr jerr;
    cinfo.err = jpeg_std_error(&jerr.pub);
    jerr.pub.error_exit = my_error_exit;
    if (setjmp(jerr.setjmp_buffer)) {
      /* If we get here, the JPEG code has signaled an error.
       * We need to clean up the JPEG object, and throw an exception.
       */
      jpeg_destroy_decompress(&cinfo);
      throw bad_format("libJPEG could not open your jpeg data!");
    }

    jpeg_create_decompress(&cinfo);

    //Load jpeg data in memory
    is.seekg(0, std::ios_base::end);
    size_t bufLength = is.tellg();
    is.seekg(0, std::ios_base::beg);
    std::vector<char> jpegBuffer(bufLength);
    is.read(jpegBuffer.data(), bufLength);

    //Attach this memory buffer to jpeg decompressor
    jpeg_mem_src(&cinfo, reinterpret_cast<unsigned char*>(jpegBuffer.data()), bufLength);

    //Read jpeg header
    jpeg_read_header(&cinfo, TRUE);

    //Set decompression options
    cinfo.dct_method = JDCT_ISLOW;

    //Start jpeg decompression
    jpeg_start_decompress(&cinfo);

    //Initialize CPrivateImaGLData
    CPrivateImaGLData ret(cinfo.output_width, cinfo.output_height, cinfo.output_components == 1 ? CImaGL::EPixelFormat::R : CImaGL::EPixelFormat::RGB, CImaGL::EPixelType::UByte);

    std::vector<std::byte*> row_pointers;
    row_pointers.resize(ret.height());
    //Flip image since OpenGL expects texture to be read from bottom to top
    for (size_t i = 0; i < ret.height(); ++i)
      row_pointers[ret.height() - i - 1] = ret.data().data() + i * ret.width() * ret.pixelSize();

    //Read jpeg scanlines
    while (cinfo.output_scanline < cinfo.output_height)
      jpeg_read_scanlines(&cinfo, reinterpret_cast<JSAMPARRAY>(row_pointers.data() + cinfo.output_scanline), ret.height());
    
    //Be polite and free memory
    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);

    return ret;
  }

}

#endif