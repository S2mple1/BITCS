cmake_minimum_required(VERSION 3.16)
project(Compilerlab4)

set(CMAKE_CXX_STANDARD 14)

# 使用 cmake 的 flex 模块
include(FindFLEX)
if(FLEX_FOUND)
    message("Info: flex found!")
else()
    message("Error: flex not found!")
endif()

# 使用 cmake 的 bison 模块
include(FindBISON)
if(BISON_FOUND)
    message("Info: bison found!")
else()
    message("Error: bison not found!")
endif()

# 为了 flex 增头文件搜索路径
include_directories(${CMAKE_SOURCE_DIR}
        ${CMAKE_CURRENT_BINARY_DIR})

# 指定 bison 编译目标
BISON_TARGET(MyParser parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp)

# 指定 flex 编译目标
FLEX_TARGET(MyScanner lexer.l ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp)

add_compile_options(-pedantic)

add_executable(Compilerlab4
        ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp
        ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp
        ${BISON_MyParser_OUTPUTS}
        ${FLEX_MyScanner_OUTPUTS}
        lexer.l
        parser.y
        tokens.cpp
)

target_compile_features(Compilerlab4 PRIVATE cxx_std_14)