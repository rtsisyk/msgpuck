project(msgpuck)
cmake_minimum_required(VERSION 2.8.5)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -fPIC -fstrict-aliasing")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall -Wextra -Werror")

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING
        "Build type, options are: Debug Release." FORCE)
endif()

include(CheckCCompilerFlag)
check_c_compiler_flag("-mno-unaligned-access" CC_HAS_MNO_UNALIGNED_ACCESS)

add_library(msgpuck STATIC msgpuck.c hints.c)
set_target_properties(msgpuck PROPERTIES VERSION 1.0 SOVERSION 1)
set_target_properties(msgpuck PROPERTIES OUTPUT_NAME "msgpuck")

if (NOT ${PROJECT_SOURCE_DIR} STREQUAL ${CMAKE_SOURCE_DIR})
    # Embedded mode, skip tests, documentation and the install targets
    return()
endif()

option(ENABLE_GCOV "Enable integration with gcov, a code coverage program" OFF)
if (ENABLE_GCOV)
    set(_flags "-fprofile-arcs -ftest-coverage")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${_flags}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${_flags}")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} ${_flags}")
endif()

add_subdirectory(test)

include(GNUInstallDirs)
install(TARGETS msgpuck
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    COMPONENT library)
install(FILES msgpuck.h DESTINATION include)

find_package(Doxygen)
if(NOT DOXYGEN_FOUND)
    return()
endif()

set(GENERATE_HTML "NO")
set(GENERATE_MAN "YES")
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in"
               "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile.man")
add_custom_command(OUTPUT doc/man/man3/msgpuck.h.3
    COMMAND ${CMAKE_COMMAND} -E make_directory doc/man
    COMMAND ${DOXYGEN_EXECUTABLE} "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile.man"
    WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
    DEPENDS msgpuck.h
    COMMENT "Generating man pages" VERBATIM)
add_custom_target(man DEPENDS doc/man/man3/msgpuck.h.3)

set(GENERATE_HTML "YES")
set(GENERATE_MAN "NO")
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in"
               "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile.html")
add_custom_command(OUTPUT doc/html/index.html
    COMMAND ${CMAKE_COMMAND} -E make_directory doc/html
    COMMAND ${DOXYGEN_EXECUTABLE} "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile.html"
    COMMAND ${CMAKE_COMMAND} -E rename doc/html/msgpuck_8h.html
                                       doc/html/index.html
    COMMAND sed s/msgpuck_8h\\.html/index\\.html/ -i doc/html/index.html
    WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
    DEPENDS msgpuck.h
    COMMENT "Generating html documentation" VERBATIM)
add_custom_target(html DEPENDS doc/html/index.html)

add_custom_target(doc DEPENDS man html)
