add_library(ArithmExpr STATIC ArithmExpr.hpp ArithmExpr.cpp)

target_include_directories(ArithmExpr PUBLIC ../include)

target_include_directories(ArithmExpr PUBLIC ../parser)
target_link_libraries(ArithmExpr parser)
