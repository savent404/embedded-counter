cmake_minimum_required(VERSION 3.10)

project(ecounter)

include(cmake/CPM.cmake)

CPMAddPackage(
    NAME gtest
    GITHUB_REPOSITORY google/googletest
    GIT_TAG release-1.10.0
    VERSION 1.10.0
    OPTIONS
        "INSTALL_GTEST OFF"
        "gtest_force_shared_crt ON"
)

set(ECOUNTER_INC ${CMAKE_CURRENT_LIST_DIR}/..)
aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/test ECOUNTER_TEST)
aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/src ECOUNTER_SRC)

add_library(ecounter STATIC ${ECOUNTER_SRC})
target_include_directories(ecounter PUBLIC ${ECOUNTER_INC})

add_executable(ecounter_test ${ECOUNTER_TEST})
target_link_libraries(ecounter_test gtest_main ecounter)
