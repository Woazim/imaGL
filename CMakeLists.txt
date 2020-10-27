# CMakeList.txt : fichier projet CMake de niveau supérieur, effectuez une configuration globale
# et incluez les sous-projets ici.
#
cmake_minimum_required (VERSION 3.8)

execute_process(COMMAND "conan" "install" "${CMAKE_BINARY_DIR}/.." "-s" "build_type=Release")
execute_process(COMMAND "conan" "install" "${CMAKE_BINARY_DIR}/.." "-s" "build_type=Debug")

project ("ImaGL")

option(BUILD_TEST "Build test program" OFF)
option(STATIC_LIB "Build ImaGL as a static library" OFF)

include(${CMAKE_BINARY_DIR}/conanbuildinfo_multi.cmake)
conan_basic_setup()

# Incluez les sous-projets.
add_subdirectory ("ImaGL")

if(BUILD_TEST)
	add_subdirectory ("test")
endif()