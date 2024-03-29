# imaGL Readme

[![Build Status](https://app.travis-ci.com/Woazim/imaGL.svg?branch=master)](https://app.travis-ci.com/Woazim/imaGL)

## About

imaGL is a lightweight C++ library that simplifies reading image file for OpenGL applications.

The following example shows how to use it in your client application:

First, you have to include imaGL header:

``` cpp
#include <imaGL/imaGL.h>
```

Then, wherever you want to access pixels data of an image, you just have to:

``` cpp
//Construct a CImaGL object:
//  from a file:
imaGL::CImaGL img1("image.png");
//  or from memory through an std::istream stream:
imaGL::CImaGL img2(stream, "PNG ");
```

_Note that the `"PNG "` argument is cast to a `imaGL::CFileFormat` object that guessed the data format of the memory_

`CImaGL` class has some accessors to read data:

``` cpp
imaGL::CImaGL img("image.png");
size_t w = img.width(); // This is... the pixel width of img
size_t h = img.height(); // This is... the pixel height of img
imaGL::CImaGL::EPixelFormat pf = img.pixelformat(); //This enum is directly compatible with `format` parameter of glTexImage2D.
// You just have to static_cast<GLenum> it.
imaGL::CImaGL::EPixelType pt = img.pixeltype(); //This enum is directly compatible with `type` parameter of glTexImage2D.
// You just have to static_cast<GLenum> it.
size_t ps = img.pixelsize(); //This is a convenient function which returns the size of a pixel in bytes.
// For example, the pixesize is 8 for an RGBA / UShort image.
const std::byte* pixels = img.pixels(); //Finally, access to pixels
```

Image are described row by row from top left corner to bottom right one. There is no gap (such as memory alignement) between rows.

Pixel format and type are choosen to be as close as the one in the file, with never loosing data.

Some helper class templates can be usefull to read/write pixels. The most important is `Pixel<CImaGL::EPixelFormat pf, CImaGL::EPixelType pt>` that you can cast from `CImaGL::pixels()`.

``` cpp
//Suppose that img is a RGBA / UShort image.
//You can access pixels in correct form with :
using PixelType = imaGL::Pixel<imaGL::CImaGL::EPixelFormat::RGBA, imaGL::CImaGL::EPixelType::UShort>;
const PixelType* pix = reinterpret_cast<const PixelType*>(img.pixels());
//Get the pixel at position row = 4, col = 42:
const PixelType& pix_4_42 = pix[4*img.width() + 42];
//Get its color components with template function:
unsigned short R = pix_4_42.comp<0>(); //Red
unsigned short G = pix_4_42.comp<1>(); //Green
unsigned short B = pix_4_42.comp<2>(); //Blue
unsigned short A = pix_4_42.comp<3>(); //Alpha
//Get its color components with "normal" function (but not so efficiently):
unsigned short _R = pix_4_42.comp_i_(0); //Red
unsigned short _G = pix_4_42.comp_i_(1); //Green
unsigned short _B = pix_4_42.comp_i_(2); //Blue
unsigned short _A = pix_4_42.comp_i_(3); //Alpha

//You can also write data to pixel with:
PixelType* pixW = reinterpret_cast<PixelType*>(img.pixels());
PixelType& pixW_4_42 = pixW[4*img.width() + 42];
//Set its color components with template function:
pixW_4_42.comp<0>(R); //Red
pixW_4_42.comp<1>(G); //Green
pixW_4_42.comp<2>(B); //Blue
pixW_4_42.comp<3>(A); //Alpha
//Set its color components with "normal" function (but not so efficiently):
pixW_4_42.comp_i_(0, R); //Red
pixW_4_42.comp_i_(1, G); //Green
pixW_4_42.comp_i_(2, B); //Blue
pixW_4_42.comp_i_(3, A); //Alpha
```

The last example also work if pixel is a packed type (such as `imaGL::CImaGL::EPixelType::UByte_5_5_3`).

## Compilation / Installation / Testing

### Prerequisites

To compile, you must have conan installed (see [conan.io](https://conan.io)). It will install and eventually build all needed dependencies.

For your information, imaGL can depend on (not necessarily, see below):

- libpng 1.6.37+ / zlib 1.2.11
- libjpeg 9d
- catch2 2.13.2+

imaGL can be built with Microsoft Visual Studio 2019 (16+), GCC 9+, CLang 10+, Apple-CLang 11.0.3+ (Xcode 11.4+).

### Quick install

imaGL use CMake as build system. To compile imaGL just open a shell and use following commands:

``` sh
cd <ImaGL_source_dir>
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release
cmake --install . --config Release
```

This invocation should configure, build then install imaGL. It has been tested on Windows 10 with Visual Studio 2019 (16.2+), on Linux (Ubuntu 20.04) with gcc 9.3 and clang 10.0.0 and on Mac OSX Catalina (10.15.5) with XCode 11.4.1 (Apple-CLang 11.0.3).

Optionnaly, you can append `--prefix <dir>` at `cmake --install` command line to choose your installation directory.

### Customizing compilation and installation

You can use cmake-gui or ccmake to configure your build. Possible options are:

- BUILD_DOCUMENTATION
  - Allows to build doxygen documentation
  - Dependencies
    - doxygen. You must install doxygen first by your own.
    - dot tool from graphviz. I asked cmake to not to force it, but it doesn't want...
  - Default OFF
- BUILD_TESTING
  - Allows to build unit tests
  - Dependencies catch2 >= 2.13.2
  - Default OFF
- STATIC_LIB
  - Build imaGL as a static (ON) or dynamic (OFF) library
  - Default OFF
- ENABLE_MULTITHREAD
  - Build ImaGL with multithread support
  - Default ON
- SUPPORT_PNG
  - Brings PNG format support to imaGL
  - Dependencies libPNG >= 1.6.37 / zlib 1.2.11
  - Default ON
- SUPPORT_JPEG
  - Brings JPEG format support to imaGL
  - Dependencies libJPEG 9d
  - Default ON
- CONAN_PROFILE
  - Define the conan profile to use to build and install dependencies.
  - Default : default

If you use mono config cmake generator (such as Unix Makefile or Ninja), you can choose `Debug` or `Release` compilation by using `-DCMAKE_BUILD_TYPE=<CONFIG>` option when configuring your build (or by using cmake-gui / ccmake)

If you use multi config cmake generator (such as Visual Studio or X Code), you can choose `Debug` or `Release` configuration in your IDE or by passing `--config <CONFIG>` option at `cmake --build` command.

### Testing

imaGL supports CMake testing. You must build imaGL with `BUILD_TESTING` option set to `ON`.

``` sh
cd <ImaGL_source_dir>
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTING=ON
cmake --build . --config Release
ctest -C Release
```

## In the future

I will add:

- More file format support
