cmake_minimum_required (VERSION 3.8)

project("testProg")

# Ajoutez une source à l'exécutable de ce projet.
add_executable (testProg)
file(GLOB testProg_SRC "*.h" "*.cpp")
target_sources(testProg PRIVATE ${testProg_SRC})

if(STATIC_LIB)
    add_compile_definitions(IMAGL_STATIC)
endif()

set_property(TARGET testProg PROPERTY CXX_STANDARD 20)

if(TARGET CONAN_PKG::libpng)
    target_link_libraries(testProg CONAN_PKG::libpng)
endif()
if(TARGET CONAN_PKG::catch2)
    target_link_libraries(testProg CONAN_PKG::catch2)
endif()

target_link_libraries(testProg libImaGL)

add_custom_command(TARGET testProg POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_if_different 
                       "${CMAKE_CURRENT_SOURCE_DIR}/test-16b.png"
                       "${CMAKE_CURRENT_SOURCE_DIR}/test-16b.rgba"
                       "${CMAKE_CURRENT_SOURCE_DIR}/test-8b.png"
                       "${CMAKE_CURRENT_SOURCE_DIR}/test-8b.rgba"
                       $<TARGET_FILE:libImaGL>
                           $<TARGET_FILE_DIR:testProg>)

set_property(TARGET testProg PROPERTY VS_DEBUGGER_WORKING_DIRECTORY $<TARGET_FILE_DIR:testProg>)

add_test(NAME Reading_16b_RGBA_PNG COMMAND testProg [read-16b-rgba] WORKING_DIRECTORY $<TARGET_FILE_DIR:testProg>)
add_test(NAME Reading_8b_RGBA_PNG COMMAND testProg [read-8b-rgba] WORKING_DIRECTORY $<TARGET_FILE_DIR:testProg>)
# TODO: Ajoutez des tests et installez des cibles si nécessaire.
