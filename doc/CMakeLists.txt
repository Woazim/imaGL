#Build Documentation

find_package(Doxygen OPTIONAL_COMPONENTS dot)

set(DOXYGEN_OUTPUT_DIRECTORY "doc")
set(DOXYGEN_EXAMPLE_PATH "../imaGL")
set(DOXYGEN_SHOW_USED_FILES NO)
set(DOXYGEN_VERBATIM_HEADER NO)
set(DOXYGEN_FULL_PATH_NAMES NO)

#Create the script that will format Readme.md each time it has been modified
set(DOC_SCRIPT
"
#This policy must be set when reading string list from file. See https://cmake.org/cmake/help/v3.19/policy/CMP0007.html
cmake_policy(SET CMP0007 NEW)

#Open Readme.md to modify some stuff for doxygen
file(STRINGS \${CURRENT_SOURCE_DIR}/../Readme.md DOC_MAINPAGE)

#Instruct doxygen that this header is for the mainpage
list(POP_FRONT DOC_MAINPAGE DOC_MAINPAGE_HEADER)
set(DOC_MAINPAGE_HEADER_MODIFIED \"\${DOC_MAINPAGE_HEADER} {#mainpage}\")
file(READ \${CURRENT_SOURCE_DIR}/../Readme.md DOC_MAINPAGE)

#CMake think that DOC_MAINPAGE is a list, since there are some semicolon in the file
#So, I join the whole list by putting \"@SEMICOLON@\" between elements
list(JOIN DOC_MAINPAGE \"@SEMICOLON@\" DOC_MAINPAGE)
string(REPLACE \"\${DOC_MAINPAGE_HEADER}\" \"\${DOC_MAINPAGE_HEADER_MODIFIED}\" DOC_MAINPAGE \${DOC_MAINPAGE})

#Replace language name to be understood by doxygen
string(REPLACE \"``` cpp\" \"```{.cpp}\" DOC_MAINPAGE \${DOC_MAINPAGE})

#Finaly, write the modified Readme.md and replacing \"@SEMICOLON@\" by semicolon (using the ascii value 59 = 0x3B otherwise, CMake will think its a f** list)
#This replacement use OS shell scripts since cmake doesn't want to write semicolon! (still list problem)
if(WIN32)
	file(WRITE \${CURRENT_BINARY_DIR}/Readme.md.in \${DOC_MAINPAGE})
	execute_process(COMMAND powershell -Command \"& {(Get-Content ./Readme.md.in) -replace '@SEMICOLON@',[char]59 | Set-Content -Path ./Readme.md}\" WORKING_DIRECTORY \${CURRENT_BINARY_DIR})
else()
	file(WRITE \${CURRENT_BINARY_DIR}/Readme.md \${DOC_MAINPAGE})
	execute_process(COMMAND sed -i \"s/@SEMICOLON@/\\\\x3b/g\" ./Readme.md WORKING_DIRECTORY \${CURRENT_BINARY_DIR})
endif()
"
)

file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/cmake-doc.script ${DOC_SCRIPT})

#run the script once to create a first version of formatted Readme.md
execute_process(COMMAND cmake -DCURRENT_BINARY_DIR=${CMAKE_CURRENT_BINARY_DIR} -DCURRENT_SOURCE_DIR=${CMAKE_CURRENT_SOURCE_DIR} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake-doc.script)

doxygen_add_docs(documentation ../imaGL/public/imaGL/imaGL.h "${CMAKE_CURRENT_BINARY_DIR}/Readme.md" ALL USE_STAMP_FILE)

add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/Readme.md 
  COMMAND cmake 
  ARGS -DCURRENT_BINARY_DIR=${CMAKE_CURRENT_BINARY_DIR} -DCURRENT_SOURCE_DIR=${CMAKE_CURRENT_SOURCE_DIR} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake-doc.script
  DEPENDS ../Readme.md
  COMMENT "Formatting Readme.md for doxygen")

install(DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/doc" DESTINATION .)
