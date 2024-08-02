find_package(GTest REQUIRED)

include( GoogleTest )
enable_testing()
file( GLOB TestSources ${CMAKE_SOURCE_DIR}/test/*.cpp )

add_executable( ${PROJECT_NAME}-test ${TestSources} )

target_link_libraries(${PROJECT_NAME}-test gtest::gtest)
gtest_discover_tests( ${PROJECT_NAME}-test WORKING_DIRECTORY
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

configure_file(${CMAKE_SOURCE_DIR}/test/frames_parser.log ${CMAKE_CURRENT_BINARY_DIR}/frames_parser.log COPYONLY)