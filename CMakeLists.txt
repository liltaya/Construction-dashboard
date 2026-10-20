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

    src/csv/CsvParser.cpp
    src/csv/CsvImporter.cpp

    src/database/Database.cpp
    src/repositories/ConstructionRepository.cpp
    src/services/DashboardService.cpp
    src/analytics/AnalyticsEngine.cpp

    include/construction/MainWindow.h

    include/construction/database/Database.h
    include/construction/repositories/ConstructionRepository.h
    include/construction/services/DashboardService.h
    include/construction/analytics/AnalyticsEngine.h

    include/construction/models/Project.h
    include/construction/models/Task.h
    include/construction/models/Worker.h
    include/construction/models/CostEntry.h
    include/construction/models/Incident.h
    include/construction/models/WorkLog.h
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
        GTest::gtest_main
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
        tests/csv_import_test.cpp
        tests/analytics_test.cpp

        src/csv/CsvParser.cpp
        src/csv/CsvImporter.cpp
        src/analytics/AnalyticsEngine.cpp
    )

    target_include_directories(
        ConstructionDashboardTests
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/include
    )

    target_link_libraries(
        ConstructionDashboardTests
        PRIVATE
            Qt6::Core
            GTest::gtest_main
    )

    include(GoogleTest)

    gtest_discover_tests(
        ConstructionDashboardTests
    )

endif()
