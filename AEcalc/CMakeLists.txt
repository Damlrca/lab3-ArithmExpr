add_executable(AEcalc main.cpp ../include/Stack.hpp ../include/Queue.hpp ../include/uninit_mem.hpp)

target_include_directories(AEcalc PUBLIC ../include)

target_include_directories(AEcalc PUBLIC ../parser)
target_link_libraries(AEcalc parser)

target_include_directories(AEcalc PUBLIC ../ArithmExpr)
target_link_libraries(AEcalc ArithmExpr)
