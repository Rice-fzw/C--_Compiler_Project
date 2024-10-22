cmake_minimum_required(VERSION 3.10)
project(MipsAssembler)

# 启用测试
enable_testing()

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 下载并配置 Google Test
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.13.0.zip
)
FetchContent_MakeAvailable(googletest)

# 添加头文件目录
include_directories(${PROJECT_SOURCE_DIR}/include)

# 创建主程序的库
add_library(mips_lib
    src/MipsLexer.cpp
)

# 创建主程序可执行文件
add_executable(mips_assembler 
    src/main.cpp
)
target_link_libraries(mips_assembler mips_lib)

# 添加测试可执行文件
add_executable(mips_tests
    tests/LexerTests.cpp
)
target_link_libraries(mips_tests
    GTest::gtest_main
    mips_lib
)

# 添加测试
include(GoogleTest)
gtest_discover_tests(mips_tests)