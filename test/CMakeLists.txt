cmake_minimum_required (VERSION 3.8)

project("test")

# Ajoutez une source à l'exécutable de ce projet.
add_executable (test)
file(GLOB test_SRC "*.h" "*.cpp")
target_sources(test PRIVATE ${test_SRC})

if(STATIC_LIB)
    add_compile_definitions(IMAGL_STATIC)
endif()

set_property(TARGET test PROPERTY CXX_STANDARD 20)

if(TARGET CONAN_PKG::libpng)
    target_link_libraries(test CONAN_PKG::libpng)
endif()
if(TARGET CONAN_PKG::catch2)
    target_link_libraries(test CONAN_PKG::catch2)
endif()

target_link_libraries(test libImaGL)

add_custom_command(TARGET test POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_if_different 
                       "${CMAKE_CURRENT_SOURCE_DIR}/test-16b.png"
                       "${CMAKE_CURRENT_SOURCE_DIR}/test-16b.rgba"
                       "${CMAKE_CURRENT_SOURCE_DIR}/test-8b.png"
                       "${CMAKE_CURRENT_SOURCE_DIR}/test-8b.rgba"
                       $<TARGET_FILE:libImaGL>
                           $<TARGET_FILE_DIR:test>)

set_property(TARGET test PROPERTY VS_DEBUGGER_WORKING_DIRECTORY $<TARGET_FILE_DIR:test>)
# TODO: Ajoutez des tests et installez des cibles si nécessaire.
