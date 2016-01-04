include_directories("../")

set(alltests)
foreach (test msgpuck)
    add_executable(${test}.test ${test}.c test.c)
    target_link_libraries(${test}.test msgpuck)

    list(APPEND alltests ${test}.test_run)
    add_custom_target(${test}.test_run
        DEPENDS ${test}.test
        COMMAND ${PROJECT_BINARY_DIR}/test/${test}.test 1> /dev/null)
endforeach()

add_custom_target(test DEPENDS ${alltests})
