cmake_minimum_required(VERSION 3.10)

project(TickBacktester CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

set(SOURCES
    main.cpp
    BacktestEngine.cpp
    DataHandler.cpp
    ExecutionHandler.cpp
    Portfolio.cpp
    Strategy.cpp
)

add_executable(backtester ${SOURCES})

# for GTest

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.12.1
)
FetchContent_MakeAvailable(googletest)

add_executable(run_tests test_indicators.cpp)

target_link_libraries(run_tests gtest_main)