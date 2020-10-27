cmake_minimum_required (VERSION 3.8)

project("test")

# Ajoutez une source à l'exécutable de ce projet.
add_executable (test)
file(GLOB test_SRC "*.h" "*.cpp")
target_sources(test PUBLIC ${test_SRC})

if(STATIC_LIB)
    add_compile_definitions(IMAGL_STATIC)
endif()

set_property(TARGET test PROPERTY CXX_STANDARD 20)

foreach(_LIB ${CONAN_LIBS_RELEASE})
    target_link_libraries(test optimized ${_LIB})
endforeach()
foreach(_LIB ${CONAN_LIBS_DEBUG})
    target_link_libraries(test debug ${_LIB})
endforeach()

target_link_libraries(test optimized ImaGL)
target_link_libraries(test debug ImaGL)


file(COPY "test-16b.png" DESTINATION ".")
file(COPY "test-16b.rgba" DESTINATION ".")
file(COPY "test-8b.png" DESTINATION ".")
file(COPY "test-8b.rgba" DESTINATION ".")
# TODO: Ajoutez des tests et installez des cibles si nécessaire.
