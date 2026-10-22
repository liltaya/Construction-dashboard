# CMake generated Testfile for 
# Source directory: /Users/tayamamenko/Developer/Construction-dashboard
# Build directory: /Users/tayamamenko/Developer/Construction-dashboard/build-asan
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test("ConstructionDashboardAllTests" "/Users/tayamamenko/Developer/Construction-dashboard/build-asan/ConstructionDashboardTests")
set_tests_properties("ConstructionDashboardAllTests" PROPERTIES  _BACKTRACE_TRIPLES "/Users/tayamamenko/Developer/Construction-dashboard/CMakeLists.txt;160;add_test;/Users/tayamamenko/Developer/Construction-dashboard/CMakeLists.txt;0;")
subdirs("_deps/googletest-build")
