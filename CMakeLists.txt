# CMakeList.txt : fichier projet CMake de niveau supérieur, effectuez une configuration globale
# et incluez les sous-projets ici.
#
cmake_minimum_required (VERSION 3.8)


project ("ImaGL")

option(BUILD_TEST "Build test program" OFF)
option(STATIC_LIB "Build ImaGL as a static library" OFF)
option(SUPPORT_PNG "Build ImaGL with PNG file format support" ON)

execute_process(COMMAND "conan" "install" "${CMAKE_SOURCE_DIR}" "-s" "build_type=Release")
execute_process(COMMAND "conan" "install" "${CMAKE_SOURCE_DIR}" "-s" "build_type=Debug")
include(${CMAKE_BINARY_DIR}/conan_paths.cmake)

if(SUPPORT_PNG)
	find_package(PNG)
endif()

set(CMAKE_DEBUG_POSTFIX d)

# Incluez les sous-projets.
add_subdirectory ("ImaGL")

if(BUILD_TEST)
	find_package(Catch2)
	add_subdirectory ("test")
endif()