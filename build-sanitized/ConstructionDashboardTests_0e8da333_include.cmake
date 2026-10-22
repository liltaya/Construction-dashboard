if(EXISTS "/Users/tayamamenko/Developer/Construction-dashboard/build-sanitized/ConstructionDashboardTests")
  discover_tests(
    COMMAND "/opt/homebrew/bin/cmake"
      -D [[TEST_EXECUTABLE=/Users/tayamamenko/Developer/Construction-dashboard/build-sanitized/ConstructionDashboardTests]]
      -D [[TEST_EXECUTOR=]]
    DISCOVERY_ARGS
      -D [[TEST_FILTER=]]
      -D [[TEST_DISCOVERY_EXTRA_ARGS=]]
      -D [[NO_PRETTY_TYPES=FALSE]]
      -D [[NO_PRETTY_VALUES=FALSE]]
      -P [[/opt/homebrew/share/cmake/Modules/GoogleTest/DiscoverTests.cmake]]
    DISCOVERY_MATCH
      "-- ([^#]+)#([^#]+)#DISABLED=([^#]+)#LOCATION=([^#]*)#"
    DISCOVERY_PROPERTIES
      TIMEOUT [[60]]
      WORKING_DIRECTORY [[/Users/tayamamenko/Developer/Construction-dashboard/build-sanitized]]
    TEST_NAME [[\1]]
    TEST_ARGS
      -D [[TEST_FILTER=\2]]
      -D [[TEST_XML_OUTPUT=]]
      -D [[TEST_EXTRA_ARGS=]]
      -P [[/opt/homebrew/share/cmake/Modules/GoogleTest/LaunchTest.cmake]]
    TEST_PROPERTIES
      DISABLED [[\3]]
      DEF_SOURCE_LINE [[\4]]
      SKIP_REGULAR_EXPRESSION "\\[  SKIPPED \\]"
      WORKING_DIRECTORY [[/Users/tayamamenko/Developer/Construction-dashboard/build-sanitized]]
      
    TEST_LIST ConstructionDashboardTests_TESTS
  )
  list(TRANSFORM ConstructionDashboardTests_TESTS REPLACE ";" "\n")
  list(FILTER ConstructionDashboardTests_TESTS EXCLUDE REGEX "(\\[|])")
  list(TRANSFORM ConstructionDashboardTests_TESTS REPLACE "\n" [[\\;]])
else()
  add_test(ConstructionDashboardTests_NOT_BUILT ConstructionDashboardTests_NOT_BUILT)
endif()
