cmake_minimum_required(VERSION 3.10)

#项目名称
project(test)
message(STATUS "Compiler ID: ${CMAKE_CXX_COMPILER_ID}")
set(CMAKE_BUILD_TYPE Debug)

#指定头文件路径
include_directories(
    ${PROJECT_SOURCE_DIR}/src/
    ${PROJECT_SOURCE_DIR}/include/uthash/
)

#指定源文件，仅有此处包含的文件会参与编译
file(GLOB SRC_FILES CONFIGURE_DEPENDS
"${PROJECT_SOURCE_DIR}/src/*.c"
"${PROJECT_SOURCE_DIR}/leetcode/*.c"
"${PROJECT_SOURCE_DIR}/leetcode/*.cpp"
"${PROJECT_SOURCE_DIR}/main.cpp")

#添加宏定义
add_definitions()

add_executable(${CMAKE_PROJECT_NAME} ${SRC_FILES})
