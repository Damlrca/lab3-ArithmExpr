add_executable(sample main.cpp ../include/parser.hpp ../include/Stack.hpp)

target_include_directories(sample PUBLIC ../include)
