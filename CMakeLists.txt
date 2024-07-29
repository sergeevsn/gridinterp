cmake_minimum_required(VERSION 3.10)
project(gridinterp)

# Specify the source files and header files
set(SOURCES
    source/interplib.cpp  
    source/main.cpp
     
)

set(HEADERS
   include/interplib.h
   include/grid.h
)

# Add include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Find the GSL package
find_package(GSL REQUIRED)

# Include the GSL headers
include_directories(${GSL_INCLUDE_DIRS})

# Add your executable
add_executable(gridinterp ${SOURCES} ${HEADERS})

# Link against the GSL library
target_link_libraries(gridinterp ${GSL_LIBRARIES})