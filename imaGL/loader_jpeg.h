#pragma once
#include "loader.h"
#include "public/imaGL/imaGL.h"

#ifdef _HAS_JPEG
#include <jpeglib.h>
#include <csetjmp>

namespace imaGL {

  class CLoaderJPEG :
    public ILoader
  {
    struct my_error_mgr {
      struct jpeg_error_mgr pub;	/* "public" fields */

      jmp_buf setjmp_buffer;	/* for return to caller */
    };
    static void my_error_exit(j_common_ptr cinfo)
    {
      /* cinfo->err really points to a my_error_mgr struct, so coerce pointer */
      my_error_mgr* myerr = (my_error_mgr*)cinfo->err;

      /* Always display the message. */
      /* We could postpone this until after returning, if we chose. */
      (*cinfo->err->output_message) (cinfo);

      /* Return control to the setjmp point */
      longjmp(myerr->setjmp_buffer, 1);
    }

  public:
    CPrivateImaGLData load(std::istream& is) override;
  };

}

#endif