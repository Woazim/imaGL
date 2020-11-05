# CMakeList.txt : projet CMake pour ImaGL2, incluez la source et définissez
# la logique spécifique au projet ici.
#
cmake_minimum_required (VERSION 3.8)

project("libImaGL")

# Ajoutez une source à l'exécutable de ce projet.

if(STATIC_LIB)
    add_library (libImaGL STATIC)
    add_compile_definitions(IMAGL_STATIC)
else()
    add_library (libImaGL SHARED)
endif()
set(OUTPUT_NAME imaGL)

if(TARGET CONAN_PKG::libpng)
    add_compile_definitions(_HAS_PNG)
    target_link_libraries (libImaGL CONAN_PKG::libpng)
endif()

file(GLOB ImaGL_SRC "*.h" "*.cpp")
target_sources(libImaGL PRIVATE ${ImaGL_SRC})

add_compile_definitions(ImaGL_EXPORTS)

set_property(TARGET libImaGL PROPERTY CXX_STANDARD 20)
set_property(TARGET libImaGL PROPERTY CXX_STANDARD_REQUIRED ON)

# TODO: Ajoutez des tests et installez des cibles si nécessaire.
