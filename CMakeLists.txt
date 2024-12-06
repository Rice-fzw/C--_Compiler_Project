cmake_minimum_required(VERSION 3.13)
project(compiler)

# settings
set(FB_EXT ".cpp")
message(STATUS "Bison generated source file extension: ${FB_EXT}")

# enable all warnings
if(MSVC)
  add_compile_options(/W3)
else()
  add_compile_options(-Wall)
endif()

# options about libraries and includes
set(LIB_DIR "opt/lib/native" CACHE STRING "directory of libraries")
set(INC_DIR "opt/include" CACHE STRING "directory of includes")
message(STATUS "Library directory:  ${LIB_DIR}")
message(STATUS "Include directory: ${INC_DIR}")

# find Bison
find_package(BISON REQUIRED)

# generate lexer/parser
file(GLOB_RECURSE Y_SOURCES "src/*.y")
if(NOT Y_SOURCES STREQUAL "")
  string(REGEX REPLACE ".*/(.*)\\.y" "${CMAKE_CURRENT_BINARY_DIR}/\\1.tab${FB_EXT}" Y_OUTPUTS "${Y_SOURCES}")
  bison_target(Parser ${Y_SOURCES} ${Y_OUTPUTS})
endif()

# project link directories
link_directories(${LIB_DIR})

# project include directories
include_directories(src)
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${INC_DIR})

# all of C++ source files
file(GLOB_RECURSE CXX_SOURCES "src/*.cpp")
set(SOURCES ${CXX_SOURCES}
            ${BISON_Parser_OUTPUT_SOURCE})

# 可执行文件
add_executable(compiler ${SOURCES})
set_target_properties(compiler PROPERTIES CXX_STANDARD 17)
target_link_libraries(compiler koopa pthread dl)