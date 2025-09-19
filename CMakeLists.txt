cmake_minimum_required(VERSION 3.17.0)

project(argparse VERSION 1.0)

# Library variables
set(LIBRARY_SRC
    src/Exceptions.cpp
    src/Argument.cpp
    src/ArgumentsParser.cpp
)

add_library(${PROJECT_NAME} STATIC ${LIBRARY_SRC})
target_include_directories(${PROJECT_NAME} PUBLIC include)
