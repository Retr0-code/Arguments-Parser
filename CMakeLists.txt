cmake_minimum_required(VERSION 3.17.0)

project(ArgParser-Lib VERSION 1.0)

set(HEADERS_PERMS
    OWNER_WRITE
    OWNER_READ
    GROUP_READ
    WORLD_READ
    )
set(LIB_PERMS
    ${HEADERS_PERMS}
    OWNER_EXECUTE
    GROUP_EXECUTE
    WORLD_EXECUTE
    )

# Configure compiler
set(CMAKE_CXX_COMPILER "/usr/bin/g++-9")

# Default binaries installation path
if(DEFINED LIB_INSTALL_PATH_BIN)
    set(CMAKE_INSTALL_PREFIX LIB_INSTALL_PATH_BIN)
endif()

# Specifies library type (static by default)
if(NOT DEFINED LIB_TYPE)
    set(LIB_TYPE STATIC)
endif()

if (DEFINED RELEASE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
    message("RELEASE")
endif()


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


add_library(arg_parser ${LIB_TYPE} ${LIBRARY_SRC} ${LIBRARY_HEAD})
set_target_properties(arg_parser PROPERTIES PUBLIC_HEADER "${LIBRARY_HEAD}")
    