project(msgpuck)
cmake_minimum_required(VERSION 2.6)

if(POLICY CMP0037)
    cmake_policy(SET CMP0037 OLD) # don't blame custom target names
endif(POLICY CMP0037)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0 -pg -Wall -Wextra")

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE RelWithDebugInfo CACHE STRING
        "Build type, options are: Debug Release." FORCE)
endif()

if (NOT CMAKE_INSTALL_LIBDIR)
   set(CMAKE_INSTALL_LIBDIR lib)
endif()

add_subdirectory(test)

add_library(${PROJECT_NAME}_shared SHARED msgpuck.c)
set_target_properties(${PROJECT_NAME}_shared PROPERTIES VERSION 0.1 SOVERSION 0)
set_target_properties(${PROJECT_NAME}_shared PROPERTIES OUTPUT_NAME "msgpuck")

install(TARGETS ${PROJECT_NAME}_shared
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    COMPONENT library)

add_library(${PROJECT_NAME}_static STATIC msgpuck.c)
set_target_properties(${PROJECT_NAME}_static PROPERTIES VERSION 0.1 SOVERSION 0)
set_target_properties(${PROJECT_NAME}_static PROPERTIES OUTPUT_NAME "msgpuck")

install(TARGETS ${PROJECT_NAME}_static
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    COMPONENT library)

install(FILES msgpuck.h DESTINATION include/msgpuck)

add_custom_target(doc
    COMMAND doxygen ${PROJECT_SOURCE_DIR}/Doxyfile)
