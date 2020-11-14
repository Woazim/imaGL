cmake_minimum_required (VERSION 3.8)

project("libImaGL")

if(STATIC_LIB)
    add_library (libImaGL STATIC)
    add_compile_definitions(IMAGL_STATIC)
else()
    add_library (libImaGL SHARED)
endif()
set_property(TARGET libImaGL PROPERTY OUTPUT_NAME imaGL)
target_include_directories(libImaGL INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/public")

if(TARGET CONAN_PKG::libpng)
    add_compile_definitions(_HAS_PNG)
    target_link_libraries (libImaGL CONAN_PKG::libpng)
endif()

file(GLOB_RECURSE ImaGL_SRC "*.h" "*.cpp")
target_sources(libImaGL PRIVATE ${ImaGL_SRC})

add_compile_definitions(ImaGL_EXPORTS)

set_property(TARGET libImaGL PROPERTY CXX_STANDARD 20)
set_property(TARGET libImaGL PROPERTY CXX_STANDARD_REQUIRED ON)

install(TARGETS libImaGL)
