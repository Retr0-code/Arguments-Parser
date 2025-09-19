cmake_minimum_required(VERSION 3.17.0)

project(argparse VERSION 1.0)

# Library variables
set(LIBRARY_SRC
    src/Exceptions.cpp
    src/Argument.cpp
    src/ArgumentsParser.cpp
)

set(LIBRARY_HEAD
    src/Exceptions.hpp;
    src/Argument.hpp;
    src/ArgumentsParser.hpp;
)

add_library(${PROJECT_NAME} ${LIB_TYPE} STATIC ${LIBRARY_HEAD})
target_include_directories(${PROJECT_NAME} include)
