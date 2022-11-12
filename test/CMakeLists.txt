add_executable(test test_main.cpp test_Stack.cpp test_Queue.cpp test_parser.cpp test_ArithmExpr.cpp)

target_include_directories(test PUBLIC ../include)

target_include_directories(test PUBLIC ../gtest)
target_link_libraries(test gtest)

target_include_directories(test PUBLIC ../parser)
target_link_libraries(test parser)

target_include_directories(test PUBLIC ../ArithmExpr)
target_link_libraries(test ArithmExpr)