project(elf2uart)

cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "-O2 -g")

# Find boost library
include(FindBoost)
find_package( Boost 1.40.0 COMPONENTS program_options REQUIRED)

# Find libelf
find_library(ELF elf)
if (NOT ELF)
  message(FATAL_ERROR "libelf library not found.")
endif()

find_path(ELF_INCLUDE_DIRS gelf.h PATH_SUFFIXES libelf)
if (NOT ELF_INCLUDE_DIRS)
  message(FATAL_ERROR "libelf headers not found.")
endif()

include_directories(include ${Boost_INCLUDE_DIRS} ${ELF_INCLUDE_DIRS})

# enable testing using ctest
enable_testing()

# add sub-directories
add_subdirectory(src)

set(dir ${CMAKE_CURRENT_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${dir} CACHE PATH "Build directory" FORCE)
set(LIBRARY_OUTPUT_PATH ${dir} CACHE PATH "Build directory" FORCE)
