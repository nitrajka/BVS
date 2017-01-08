set(core_SRCS bvs.cpp bvs.h)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_library(core ${core_SRCS})
