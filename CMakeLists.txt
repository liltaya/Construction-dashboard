cmake_minimum_required(VERSION 3.22)

project(
    ConstructionDashboard
    VERSION 0.1.0
    DESCRIPTION "Construction project analytics dashboard"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(
    Qt6
    REQUIRED
    COMPONENTS
        Core
        Widgets
        Sql
)

qt_standard_project_setup()

qt_add_executable(
    ConstructionDashboard

    src/main.cpp
    src/MainWindow.cpp

    include/construction/MainWindow.h
)

target_include_directories(
    ConstructionDashboard
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(
    ConstructionDashboard
    PRIVATE
        Qt6::Core
        Qt6::Widgets
        Qt6::Sql
)

target_compile_options(
    ConstructionDashboard
    PRIVATE
        -Wall
        -Wextra
        -Wpedantic
)

include(CTest)

if(BUILD_TESTING)

    include(FetchContent)

    FetchContent_Declare(
        googletest
        URL
        https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
    )

    FetchContent_MakeAvailable(googletest)

    add_executable(
        ConstructionDashboardTests
        tests/smoke_test.cpp
    )

    target_include_directories(
        ConstructionDashboardTests
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/include
    )

    target_link_libraries(
        ConstructionDashboardTests
        PRIVATE
            GTest::gtest_main
    )

    include(GoogleTest)

    gtest_discover_tests(
        ConstructionDashboardTests
    )

endif()