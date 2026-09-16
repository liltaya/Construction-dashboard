add_test([=[ProjectSetupTest.GoogleTestWorks]=]  /Users/tayamamenko/Developer/Construction-dashboard/build/ConstructionDashboardTests [==[--gtest_filter=ProjectSetupTest.GoogleTestWorks]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ProjectSetupTest.GoogleTestWorks]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/Users/tayamamenko/Developer/Construction-dashboard/tests/smoke_test.cpp:3]==]
    WORKING_DIRECTORY [==[/Users/tayamamenko/Developer/Construction-dashboard/build]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
set(ConstructionDashboardTests_TESTS [==[ProjectSetupTest.GoogleTestWorks]==])
