cmake_minimum_required (VERSION 3.8)

project("testProg")

add_executable (testProg)
file(GLOB testProg_SRC "*.h" "*.cpp")
target_sources(testProg PRIVATE ${testProg_SRC})

if(STATIC_LIB)
    add_compile_definitions(IMAGL_STATIC)
endif()

set_property(TARGET testProg PROPERTY CXX_STANDARD 20)

if(TARGET CONAN_PKG::libpng)
    add_compile_definitions(_HAS_PNG)
    target_link_libraries(testProg CONAN_PKG::libpng)
endif()
if(TARGET CONAN_PKG::libjpeg)
    add_compile_definitions(_HAS_JPEG)
    target_link_libraries(testProg CONAN_PKG::libjpeg)
endif()
if(TARGET CONAN_PKG::catch2)
    target_link_libraries(testProg CONAN_PKG::catch2)
endif()

target_link_libraries(testProg libImaGL)

# copy dataset files
file(GLOB datasetFiles "dataset/*.png" "dataset/*.png.txt" "dataset/*.jpg" "dataset/*.jpg.txt")
add_custom_command(TARGET testProg POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_if_different 
                       ${datasetFiles}
                           $<TARGET_FILE_DIR:testProg>)
# copy dynamic linked library
if(NOT STATIC_LIB)
    add_custom_command(TARGET testProg POST_BUILD
                       COMMAND ${CMAKE_COMMAND} -E copy_if_different 
                           $<TARGET_FILE:libImaGL>
                               $<TARGET_FILE_DIR:testProg>)
endif()

set_property(TARGET testProg PROPERTY VS_DEBUGGER_WORKING_DIRECTORY $<TARGET_FILE_DIR:testProg>)

#PNG Tests
if(SUPPORT_PNG)
    add_test(NAME Reading_basi0g01.png COMMAND testProg [basi0g01] WORKING_DIRECTORY $<TARGET_FILE_DIR:testProg>)
    add_test(NAME Reading_basi0g02.png COMMAND testProg [basi0g02] WORKING_DIRECTORY $<TARGET_FILE_DIR:testProg>)
    add_test(NAME Reading_basi0g04.png COMMAND testProg [basi0g04] WORKING_DIRECTORY $<TARGET_FILE_DIR:testProg>)
    add_test(NAME Reading_basi0g08.png COMMAND testProg [basi0g08] WORKING_DIRECTORY $<TARGET_FILE_DIR:testProg>)
    add_test(NAME Reading_basi0g16.png COMMAND testProg [basi0g16] WORKING_DIRECTORY $<TARGET_FILE_DIR:testProg>)
    add_test(NAME Reading_basi2c08.png COMMAND testProg [basi2c08] WORKING_DIRECTORY $<TARGET_FILE_DIR:testProg>)
    add_test(NAME Reading_basi2c16.png COMMAND testProg [basi2c16] WORKING_DIRECTORY $<TARGET_FILE_DIR:testProg>)
    add_test(NAME Reading_basi3p01.png COMMAND testProg [basi3p01] WORKING_DIRECTORY $<TARGET_FILE_DIR:testProg>)
    add_test(NAME Reading_basi3p04.png COMMAND testProg [basi3p04] WORKING_DIRECTORY $<TARGET_FILE_DIR:testProg>)
    add_test(NAME Reading_basi3p08.png COMMAND testProg [basi3p08] WORKING_DIRECTORY $<TARGET_FILE_DIR:testProg>)
    add_test(NAME Reading_basi4a08.png COMMAND testProg [basi4a08] WORKING_DIRECTORY $<TARGET_FILE_DIR:testProg>)
    add_test(NAME Reading_basi4a16.png COMMAND testProg [basi4a16] WORKING_DIRECTORY $<TARGET_FILE_DIR:testProg>)
    add_test(NAME Reading_basi6a08.png COMMAND testProg [basi6a08] WORKING_DIRECTORY $<TARGET_FILE_DIR:testProg>)
    add_test(NAME Reading_basi6a16.png COMMAND testProg [basi6a16] WORKING_DIRECTORY $<TARGET_FILE_DIR:testProg>)
    add_test(NAME Reading_basn0g01.png COMMAND testProg [basn0g01] WORKING_DIRECTORY $<TARGET_FILE_DIR:testProg>)
    add_test(NAME Reading_basn0g02.png COMMAND testProg [basn0g02] WORKING_DIRECTORY $<TARGET_FILE_DIR:testProg>)
    add_test(NAME Reading_basn0g04.png COMMAND testProg [basn0g04] WORKING_DIRECTORY $<TARGET_FILE_DIR:testProg>)
    add_test(NAME Reading_basn0g08.png COMMAND testProg [basn0g08] WORKING_DIRECTORY $<TARGET_FILE_DIR:testProg>)
    add_test(NAME Reading_basn0g16.png COMMAND testProg [basn0g16] WORKING_DIRECTORY $<TARGET_FILE_DIR:testProg>)
    add_test(NAME Reading_basn2c08.png COMMAND testProg [basn2c08] WORKING_DIRECTORY $<TARGET_FILE_DIR:testProg>)
    add_test(NAME Reading_basn2c16.png COMMAND testProg [basn2c16] WORKING_DIRECTORY $<TARGET_FILE_DIR:testProg>)
    add_test(NAME Reading_basn3p01.png COMMAND testProg [basn3p01] WORKING_DIRECTORY $<TARGET_FILE_DIR:testProg>)
    add_test(NAME Reading_basn3p04.png COMMAND testProg [basn3p04] WORKING_DIRECTORY $<TARGET_FILE_DIR:testProg>)
    add_test(NAME Reading_basn3p08.png COMMAND testProg [basn3p08] WORKING_DIRECTORY $<TARGET_FILE_DIR:testProg>)
    add_test(NAME Reading_basn4a08.png COMMAND testProg [basn4a08] WORKING_DIRECTORY $<TARGET_FILE_DIR:testProg>)
    add_test(NAME Reading_basn4a16.png COMMAND testProg [basn4a16] WORKING_DIRECTORY $<TARGET_FILE_DIR:testProg>)
    add_test(NAME Reading_basn6a08.png COMMAND testProg [basn6a08] WORKING_DIRECTORY $<TARGET_FILE_DIR:testProg>)
    add_test(NAME Reading_basn6a16.png COMMAND testProg [basn6a16] WORKING_DIRECTORY $<TARGET_FILE_DIR:testProg>)
    add_test(NAME Reading_z00n2c08.png COMMAND testProg [z00n2c08] WORKING_DIRECTORY $<TARGET_FILE_DIR:testProg>)
    add_test(NAME Reading_z03n2c08.png COMMAND testProg [z03n2c08] WORKING_DIRECTORY $<TARGET_FILE_DIR:testProg>)
    add_test(NAME Reading_z06n2c08.png COMMAND testProg [z06n2c08] WORKING_DIRECTORY $<TARGET_FILE_DIR:testProg>)
    add_test(NAME Reading_z09n2c08.png COMMAND testProg [z09n2c08] WORKING_DIRECTORY $<TARGET_FILE_DIR:testProg>)
    add_test(NAME Reading_test-16b.png COMMAND testProg [test-16b] WORKING_DIRECTORY $<TARGET_FILE_DIR:testProg>)

    add_test(NAME Reading_PNG_from_memory COMMAND testProg [opening-png-from-memory] WORKING_DIRECTORY $<TARGET_FILE_DIR:testProg>)
endif()

#JPEG tests
if(SUPPORT_JPEG)
    add_test(NAME Reading_test-rgb.jpg COMMAND testProg [rgbjpeg] WORKING_DIRECTORY $<TARGET_FILE_DIR:testProg>)
    add_test(NAME Reading_test-gray.jpg COMMAND testProg [grayjpeg] WORKING_DIRECTORY $<TARGET_FILE_DIR:testProg>)
    add_test(NAME Reading_JPG_from_memory COMMAND testProg [opening-jpg-from-memory] WORKING_DIRECTORY $<TARGET_FILE_DIR:testProg>)
endif()

#Generic CImaGL tests
add_test(NAME Moving_objects COMMAND testProg [move-constructor] WORKING_DIRECTORY $<TARGET_FILE_DIR:testProg>)

add_test(NAME Pixel_casts_for_reading COMMAND testProg [pixelcast-reading] WORKING_DIRECTORY $<TARGET_FILE_DIR:testProg>)
add_test(NAME Pixel_casts_for_writing COMMAND testProg [pixelcast-writing] WORKING_DIRECTORY $<TARGET_FILE_DIR:testProg>)

if(SUPPORT_PNG)
    add_test(NAME Image_scaling COMMAND testProg [scaling] WORKING_DIRECTORY $<TARGET_FILE_DIR:testProg>)
    add_test(NAME Image_scaling_pow2 COMMAND testProg [scaling-pow2] WORKING_DIRECTORY $<TARGET_FILE_DIR:testProg>)
endif()