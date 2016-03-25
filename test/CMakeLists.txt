include_directories("../")

#find_program(PROVE prove)
if (PROVE)
    set(TEST_RUNNER prove)
else()
    set(TEST_RUNNER)
endif()

set(alltests)
foreach (test msgpuck)
    add_executable(${test}.test ${test}.c test.c)
    target_link_libraries(${test}.test msgpuck)

    list(APPEND alltests ${test}.test_run)
    add_custom_target(${test}.test_run
        DEPENDS ${test}.test
        COMMAND ${TEST_RUNNER} ${PROJECT_BINARY_DIR}/test/${test}.test)
endforeach()

add_custom_target(test DEPENDS ${alltests})
