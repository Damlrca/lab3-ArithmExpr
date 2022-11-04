add_executable(test test_main.cpp test_parser.cpp)

target_include_directories(test PUBLIC ../include)

target_include_directories(test PUBLIC ../gtest)
target_link_libraries(test gtest)