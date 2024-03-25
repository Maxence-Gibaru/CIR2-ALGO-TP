cmake_minimum_required(VERSION 3.5.0)
project(TP5 VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_executable(TP5 
src/main.cpp
src/config.cpp)

include_directories(include)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
