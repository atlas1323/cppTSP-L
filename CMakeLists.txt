cmake_minimum_required(VERSION 3.23)
project(cppTSP VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_BUILD_TYPE "Debug")

set(CMAKE_GENERATOR ninja)
# because exe links to src, src must be defined first in this file
add_subdirectory(src)
add_subdirectory(app)
add_subdirectory(sandbox)
add_subdirectory(tests)
# add_executable(cppTSP main.cpp Contender.cpp Optimizers.cpp DataLog.cpp)
