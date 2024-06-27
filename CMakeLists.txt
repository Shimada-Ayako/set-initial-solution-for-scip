cmake_minimum_required(VERSION 3.29)
project(main C)
set(-std=c11)
set(CMAKE_C_COMPILER clang)
find_package(SCIP REQUIRED)
add_executable(main main.c)
target_include_directories(main PUBLIC ${SCIP_INCLUDE_DIRS})
target_link_libraries(main PUBLIC ${SCIP_LIBRARIES})







