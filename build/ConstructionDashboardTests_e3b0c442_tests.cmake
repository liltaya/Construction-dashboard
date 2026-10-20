add_test([=[ProjectSetupTest.GoogleTestWorks]=]  /Users/tayamamenko/Developer/Construction-dashboard/build/ConstructionDashboardTests [==[--gtest_filter=ProjectSetupTest.GoogleTestWorks]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ProjectSetupTest.GoogleTestWorks]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/Users/tayamamenko/Developer/Construction-dashboard/tests/smoke_test.cpp:3]==]
    WORKING_DIRECTORY [==[/Users/tayamamenko/Developer/Construction-dashboard/build]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CsvImporterTest.ImportsValidProject]=]  /Users/tayamamenko/Developer/Construction-dashboard/build/ConstructionDashboardTests [==[--gtest_filter=CsvImporterTest.ImportsValidProject]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CsvImporterTest.ImportsValidProject]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/Users/tayamamenko/Developer/Construction-dashboard/tests/csv_import_test.cpp:35]==]
    WORKING_DIRECTORY [==[/Users/tayamamenko/Developer/Construction-dashboard/build]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CsvImporterTest.RejectsInvalidProjectStatus]=]  /Users/tayamamenko/Developer/Construction-dashboard/build/ConstructionDashboardTests [==[--gtest_filter=CsvImporterTest.RejectsInvalidProjectStatus]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CsvImporterTest.RejectsInvalidProjectStatus]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/Users/tayamamenko/Developer/Construction-dashboard/tests/csv_import_test.cpp:66]==]
    WORKING_DIRECTORY [==[/Users/tayamamenko/Developer/Construction-dashboard/build]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CsvImporterTest.RejectsNegativeProjectBudget]=]  /Users/tayamamenko/Developer/Construction-dashboard/build/ConstructionDashboardTests [==[--gtest_filter=CsvImporterTest.RejectsNegativeProjectBudget]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CsvImporterTest.RejectsNegativeProjectBudget]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/Users/tayamamenko/Developer/Construction-dashboard/tests/csv_import_test.cpp:90]==]
    WORKING_DIRECTORY [==[/Users/tayamamenko/Developer/Construction-dashboard/build]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CsvImporterTest.AllowsCostWithoutTask]=]  /Users/tayamamenko/Developer/Construction-dashboard/build/ConstructionDashboardTests [==[--gtest_filter=CsvImporterTest.AllowsCostWithoutTask]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CsvImporterTest.AllowsCostWithoutTask]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/Users/tayamamenko/Developer/Construction-dashboard/tests/csv_import_test.cpp:146]==]
    WORKING_DIRECTORY [==[/Users/tayamamenko/Developer/Construction-dashboard/build]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CsvImporterTest.RejectsWrongHeader]=]  /Users/tayamamenko/Developer/Construction-dashboard/build/ConstructionDashboardTests [==[--gtest_filter=CsvImporterTest.RejectsWrongHeader]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CsvImporterTest.RejectsWrongHeader]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/Users/tayamamenko/Developer/Construction-dashboard/tests/csv_import_test.cpp:178]==]
    WORKING_DIRECTORY [==[/Users/tayamamenko/Developer/Construction-dashboard/build]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CsvParserTest.HandlesQuotedComma]=]  /Users/tayamamenko/Developer/Construction-dashboard/build/ConstructionDashboardTests [==[--gtest_filter=CsvParserTest.HandlesQuotedComma]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CsvParserTest.HandlesQuotedComma]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/Users/tayamamenko/Developer/Construction-dashboard/tests/csv_import_test.cpp:113]==]
    WORKING_DIRECTORY [==[/Users/tayamamenko/Developer/Construction-dashboard/build]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[AnalyticsEngineTest.CalculatesMetrics]=]  /Users/tayamamenko/Developer/Construction-dashboard/build/ConstructionDashboardTests [==[--gtest_filter=AnalyticsEngineTest.CalculatesMetrics]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[AnalyticsEngineTest.CalculatesMetrics]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/Users/tayamamenko/Developer/Construction-dashboard/tests/analytics_test.cpp:5]==]
    WORKING_DIRECTORY [==[/Users/tayamamenko/Developer/Construction-dashboard/build]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
set(ConstructionDashboardTests_TESTS [==[ProjectSetupTest.GoogleTestWorks]==] [==[CsvImporterTest.ImportsValidProject]==] [==[CsvImporterTest.RejectsInvalidProjectStatus]==] [==[CsvImporterTest.RejectsNegativeProjectBudget]==] [==[CsvImporterTest.AllowsCostWithoutTask]==] [==[CsvImporterTest.RejectsWrongHeader]==] [==[CsvParserTest.HandlesQuotedComma]==] [==[AnalyticsEngineTest.CalculatesMetrics]==])
