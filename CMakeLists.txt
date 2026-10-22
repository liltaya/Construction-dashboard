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

include(CTest)

option(
    ENABLE_WARNINGS
    "Enable additional compiler warnings"
    ON
)

option(
    ENABLE_SANITIZERS
    "Enable AddressSanitizer and UBSan"
    OFF
)

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

    # CSV
    src/csv/CsvParser.cpp
    src/csv/CsvImporter.cpp
    src/csv/CsvValidator.cpp

    # DATABASE
    src/database/Database.cpp

    # REPOSITORY
    src/repositories/ConstructionRepository.cpp

    # SERVICES
    src/services/DashboardService.cpp

    # ANALYTICS
    src/analytics/AnalyticsEngine.cpp

    # LOGGING
    src/utils/Logger.cpp

    # HEADERS
    include/construction/MainWindow.h

    include/construction/csv/CsvParser.h
    include/construction/csv/CsvImporter.h
    include/construction/csv/CsvValidator.h

    include/construction/logging/Logger.h

    include/construction/database/Database.h
    include/construction/repositories/ConstructionRepository.h
    include/construction/services/DashboardService.h
    include/construction/analytics/AnalyticsEngine.h

    # MODELS
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
)

if(BUILD_TESTING)

    include(FetchContent)

    FetchContent_Declare(
        googletest
        URL
            https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    )

    FetchContent_MakeAvailable(googletest)

    add_executable(
        ConstructionDashboardTests

        # TEST FILES
        tests/test_main.cpp
        tests/smoke_test.cpp
        tests/csv_import_test.cpp
        tests/csv_validation_test.cpp
        tests/analytics_test.cpp
        tests/database_test.cpp

        # CSV
        src/csv/CsvParser.cpp
        src/csv/CsvImporter.cpp
        src/csv/CsvValidator.cpp

        # ANALYTICS
        src/analytics/AnalyticsEngine.cpp

        # DATABASE
        src/database/Database.cpp

        # REPOSITORY
        src/repositories/ConstructionRepository.cpp

        # LOGGING
        src/utils/Logger.cpp
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
            Qt6::Sql
            GTest::gtest
    )

    include(GoogleTest)

   add_test(
    NAME ConstructionDashboardAllTests
    COMMAND ConstructionDashboardTests
)

endif() # BUILD_TESTING

if(ENABLE_WARNINGS)

    foreach(target
        ConstructionDashboard
        ConstructionDashboardTests
    )

        if(TARGET ${target})

            target_compile_options(
                ${target}
                PRIVATE
                    $<$<COMPILE_LANG_AND_ID:CXX,Clang,GNU>:
                        -Wall
                        -Wextra
                        -Wpedantic
                        -Wshadow
                        -Wconversion
                    >
            )

        endif()

    endforeach()

endif() # ENABLE_WARNINGS

if(ENABLE_SANITIZERS)

    if(NOT CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
        message(
            FATAL_ERROR
            "Sanitizers require Clang or GCC"
        )
    endif()

    foreach(target
        ConstructionDashboard
        ConstructionDashboardTests
    )

        if(TARGET ${target})

            target_compile_options(
                ${target}
                PRIVATE
                    -fsanitize=address,undefined
                    -fno-omit-frame-pointer
                    -g
            )

            target_link_options(
                ${target}
                PRIVATE
                    -fsanitize=address,undefined
            )

        endif()

    endforeach()

endif() # ENABLE_SANITIZERS
