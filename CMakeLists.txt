project(msgpuck)
cmake_minimum_required(VERSION 2.6)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0 -pg -Wall -Wextra")

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE RelWithDebugInfo CACHE STRING
        "Build type, options are: Debug Release." FORCE)
endif()

add_subdirectory(test)
add_library(${PROJECT_NAME} SHARED msgpuck.c)
set_target_properties(${PROJECT_NAME} PROPERTIES VERSION 0.1 SOVERSION 0)

if (NOT CMAKE_INSTALL_LIBDIR)
   set(CMAKE_INSTALL_LIBDIR lib)
endif()

install(FILES msgpuck.h DESTINATION include)
install(TARGETS ${PROJECT_NAME}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    COMPONENT library)

add_custom_target(doc
    COMMAND doxygen ${PROJECT_SOURCE_DIR}/Doxyfile)
