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
add_test([=[CsvValidatorTest.AcceptsValidCsv]=]  /Users/tayamamenko/Developer/Construction-dashboard/build/ConstructionDashboardTests [==[--gtest_filter=CsvValidatorTest.AcceptsValidCsv]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CsvValidatorTest.AcceptsValidCsv]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/Users/tayamamenko/Developer/Construction-dashboard/tests/csv_validation_test.cpp:7]==]
    WORKING_DIRECTORY [==[/Users/tayamamenko/Developer/Construction-dashboard/build]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CsvValidatorTest.RejectsEmptyFile]=]  /Users/tayamamenko/Developer/Construction-dashboard/build/ConstructionDashboardTests [==[--gtest_filter=CsvValidatorTest.RejectsEmptyFile]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CsvValidatorTest.RejectsEmptyFile]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/Users/tayamamenko/Developer/Construction-dashboard/tests/csv_validation_test.cpp:20]==]
    WORKING_DIRECTORY [==[/Users/tayamamenko/Developer/Construction-dashboard/build]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CsvValidatorTest.RejectsMissingColumn]=]  /Users/tayamamenko/Developer/Construction-dashboard/build/ConstructionDashboardTests [==[--gtest_filter=CsvValidatorTest.RejectsMissingColumn]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CsvValidatorTest.RejectsMissingColumn]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/Users/tayamamenko/Developer/Construction-dashboard/tests/csv_validation_test.cpp:28]==]
    WORKING_DIRECTORY [==[/Users/tayamamenko/Developer/Construction-dashboard/build]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CsvValidatorTest.HandlesQuotedComma]=]  /Users/tayamamenko/Developer/Construction-dashboard/build/ConstructionDashboardTests [==[--gtest_filter=CsvValidatorTest.HandlesQuotedComma]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CsvValidatorTest.HandlesQuotedComma]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/Users/tayamamenko/Developer/Construction-dashboard/tests/csv_validation_test.cpp:38]==]
    WORKING_DIRECTORY [==[/Users/tayamamenko/Developer/Construction-dashboard/build]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CsvValidatorTest.RejectsUnclosedQuote]=]  /Users/tayamamenko/Developer/Construction-dashboard/build/ConstructionDashboardTests [==[--gtest_filter=CsvValidatorTest.RejectsUnclosedQuote]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CsvValidatorTest.RejectsUnclosedQuote]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/Users/tayamamenko/Developer/Construction-dashboard/tests/csv_validation_test.cpp:54]==]
    WORKING_DIRECTORY [==[/Users/tayamamenko/Developer/Construction-dashboard/build]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CsvValidatorTest.HandlesEscapedQuotes]=]  /Users/tayamamenko/Developer/Construction-dashboard/build/ConstructionDashboardTests [==[--gtest_filter=CsvValidatorTest.HandlesEscapedQuotes]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CsvValidatorTest.HandlesEscapedQuotes]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/Users/tayamamenko/Developer/Construction-dashboard/tests/csv_validation_test.cpp:64]==]
    WORKING_DIRECTORY [==[/Users/tayamamenko/Developer/Construction-dashboard/build]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CsvValidatorTest.RejectsEmptyHeader]=]  /Users/tayamamenko/Developer/Construction-dashboard/build/ConstructionDashboardTests [==[--gtest_filter=CsvValidatorTest.RejectsEmptyHeader]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CsvValidatorTest.RejectsEmptyHeader]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/Users/tayamamenko/Developer/Construction-dashboard/tests/csv_validation_test.cpp:79]==]
    WORKING_DIRECTORY [==[/Users/tayamamenko/Developer/Construction-dashboard/build]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[AnalyticsTest.BudgetVariance]=]  /Users/tayamamenko/Developer/Construction-dashboard/build/ConstructionDashboardTests [==[--gtest_filter=AnalyticsTest.BudgetVariance]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[AnalyticsTest.BudgetVariance]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/Users/tayamamenko/Developer/Construction-dashboard/tests/analytics_test.cpp:8]==]
    WORKING_DIRECTORY [==[/Users/tayamamenko/Developer/Construction-dashboard/build]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[AnalyticsTest.CompletionPercentage]=]  /Users/tayamamenko/Developer/Construction-dashboard/build/ConstructionDashboardTests [==[--gtest_filter=AnalyticsTest.CompletionPercentage]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[AnalyticsTest.CompletionPercentage]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/Users/tayamamenko/Developer/Construction-dashboard/tests/analytics_test.cpp:34]==]
    WORKING_DIRECTORY [==[/Users/tayamamenko/Developer/Construction-dashboard/build]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[AnalyticsTest.OverdueTasks]=]  /Users/tayamamenko/Developer/Construction-dashboard/build/ConstructionDashboardTests [==[--gtest_filter=AnalyticsTest.OverdueTasks]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[AnalyticsTest.OverdueTasks]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/Users/tayamamenko/Developer/Construction-dashboard/tests/analytics_test.cpp:55]==]
    WORKING_DIRECTORY [==[/Users/tayamamenko/Developer/Construction-dashboard/build]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[AnalyticsTest.LaborHours]=]  /Users/tayamamenko/Developer/Construction-dashboard/build/ConstructionDashboardTests [==[--gtest_filter=AnalyticsTest.LaborHours]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[AnalyticsTest.LaborHours]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/Users/tayamamenko/Developer/Construction-dashboard/tests/analytics_test.cpp:78]==]
    WORKING_DIRECTORY [==[/Users/tayamamenko/Developer/Construction-dashboard/build]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[AnalyticsTest.EmptyData]=]  /Users/tayamamenko/Developer/Construction-dashboard/build/ConstructionDashboardTests [==[--gtest_filter=AnalyticsTest.EmptyData]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[AnalyticsTest.EmptyData]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/Users/tayamamenko/Developer/Construction-dashboard/tests/analytics_test.cpp:99]==]
    WORKING_DIRECTORY [==[/Users/tayamamenko/Developer/Construction-dashboard/build]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[DatabaseTest.CreatesTables]=]  /Users/tayamamenko/Developer/Construction-dashboard/build/ConstructionDashboardTests [==[--gtest_filter=DatabaseTest.CreatesTables]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[DatabaseTest.CreatesTables]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/Users/tayamamenko/Developer/Construction-dashboard/tests/database_test.cpp:34]==]
    WORKING_DIRECTORY [==[/Users/tayamamenko/Developer/Construction-dashboard/build]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[DatabaseTest.InsertAndRead]=]  /Users/tayamamenko/Developer/Construction-dashboard/build/ConstructionDashboardTests [==[--gtest_filter=DatabaseTest.InsertAndRead]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[DatabaseTest.InsertAndRead]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/Users/tayamamenko/Developer/Construction-dashboard/tests/database_test.cpp:52]==]
    WORKING_DIRECTORY [==[/Users/tayamamenko/Developer/Construction-dashboard/build]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[DatabaseTest.UpdateProject]=]  /Users/tayamamenko/Developer/Construction-dashboard/build/ConstructionDashboardTests [==[--gtest_filter=DatabaseTest.UpdateProject]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[DatabaseTest.UpdateProject]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/Users/tayamamenko/Developer/Construction-dashboard/tests/database_test.cpp:70]==]
    WORKING_DIRECTORY [==[/Users/tayamamenko/Developer/Construction-dashboard/build]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[DatabaseTest.DuplicateIdThrows]=]  /Users/tayamamenko/Developer/Construction-dashboard/build/ConstructionDashboardTests [==[--gtest_filter=DatabaseTest.DuplicateIdThrows]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[DatabaseTest.DuplicateIdThrows]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/Users/tayamamenko/Developer/Construction-dashboard/tests/database_test.cpp:93]==]
    WORKING_DIRECTORY [==[/Users/tayamamenko/Developer/Construction-dashboard/build]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[DatabaseTest.NegativeBudgetRejected]=]  /Users/tayamamenko/Developer/Construction-dashboard/build/ConstructionDashboardTests [==[--gtest_filter=DatabaseTest.NegativeBudgetRejected]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[DatabaseTest.NegativeBudgetRejected]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/Users/tayamamenko/Developer/Construction-dashboard/tests/database_test.cpp:111]==]
    WORKING_DIRECTORY [==[/Users/tayamamenko/Developer/Construction-dashboard/build]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[DatabaseTest.CountsSafetyIncidents]=]  /Users/tayamamenko/Developer/Construction-dashboard/build/ConstructionDashboardTests [==[--gtest_filter=DatabaseTest.CountsSafetyIncidents]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[DatabaseTest.CountsSafetyIncidents]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/Users/tayamamenko/Developer/Construction-dashboard/tests/database_test.cpp:128]==]
    WORKING_DIRECTORY [==[/Users/tayamamenko/Developer/Construction-dashboard/build]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
set(ConstructionDashboardTests_TESTS [==[ProjectSetupTest.GoogleTestWorks]==] [==[CsvImporterTest.ImportsValidProject]==] [==[CsvImporterTest.RejectsInvalidProjectStatus]==] [==[CsvImporterTest.RejectsNegativeProjectBudget]==] [==[CsvImporterTest.AllowsCostWithoutTask]==] [==[CsvImporterTest.RejectsWrongHeader]==] [==[CsvParserTest.HandlesQuotedComma]==] [==[CsvValidatorTest.AcceptsValidCsv]==] [==[CsvValidatorTest.RejectsEmptyFile]==] [==[CsvValidatorTest.RejectsMissingColumn]==] [==[CsvValidatorTest.HandlesQuotedComma]==] [==[CsvValidatorTest.RejectsUnclosedQuote]==] [==[CsvValidatorTest.HandlesEscapedQuotes]==] [==[CsvValidatorTest.RejectsEmptyHeader]==] [==[AnalyticsTest.BudgetVariance]==] [==[AnalyticsTest.CompletionPercentage]==] [==[AnalyticsTest.OverdueTasks]==] [==[AnalyticsTest.LaborHours]==] [==[AnalyticsTest.EmptyData]==] [==[DatabaseTest.CreatesTables]==] [==[DatabaseTest.InsertAndRead]==] [==[DatabaseTest.UpdateProject]==] [==[DatabaseTest.DuplicateIdThrows]==] [==[DatabaseTest.NegativeBudgetRejected]==] [==[DatabaseTest.CountsSafetyIncidents]==])
