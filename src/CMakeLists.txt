add_library(
    assist
    Assist/Benchmarks.h
    Assist/Benchmarks.cpp
)

# include path for library
target_include_directories(assist PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Assist")


add_library(
    optimizers
    GenOpt/Contender.h
    GenOpt/Contender.cpp
    GenOpt/DataLog.h
    GenOpt/DataLog.cpp
    GenOpt/Optimizers.h
    GenOpt/Optimizers.cpp
)

# include path for libaray
target_include_directories(optimizers PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/GenOpt")

# can set preprocessor definitions
# target_compile_definitions(<project> PUBLIC VAR_NAME=value)
# this will be propogated to anyone that uses it