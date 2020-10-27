# CMakeList.txt : projet CMake pour ImaGL2, incluez la source et définissez
# la logique spécifique au projet ici.
#
cmake_minimum_required (VERSION 3.8)

project("libImaGL")

# Ajoutez une source à l'exécutable de ce projet.
if(STATIC_LIB)
    add_library (ImaGL STATIC)
    add_compile_definitions(IMAGL_STATIC)
else()
    add_library (ImaGL SHARED)
endif()

file(GLOB ImaGL_SRC "*.h" "*.cpp")
target_sources(ImaGL PUBLIC ${ImaGL_SRC})

add_compile_definitions(ImaGL_EXPORTS)

set_property(TARGET ImaGL PROPERTY CXX_STANDARD 20)

foreach(_LIB ${CONAN_LIBS_RELEASE})
    target_link_libraries(ImaGL optimized ${_LIB})
endforeach()
foreach(_LIB ${CONAN_LIBS_DEBUG})
    target_link_libraries(ImaGL debug ${_LIB})
endforeach()

# TODO: Ajoutez des tests et installez des cibles si nécessaire.
