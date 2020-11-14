#Build Documentation

find_package(Doxygen OPTIONAL_COMPONENTS dot)

set(DOXYGEN_OUTPUT_DIRECTORY "doc")
set(DOXYGEN_EXAMPLE_PATH "../imaGL")
set(DOXYGEN_SHOW_USED_FILES NO)
set(DOXYGEN_VERBATIM_HEADER NO)
set(DOXYGEN_FULL_PATH_NAMES NO)

doxygen_add_docs(documentation ../imaGL/public/imaGL.h ALL USE_STAMP_FILE)

install(DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/doc" DESTINATION .)
