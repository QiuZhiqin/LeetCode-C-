cmake_minimum_required(VERSION 3.10)

#项目名称
project(test)

#指定源文件，仅有此处包含的文件会参与编译
file(GLOB SRC_FILES
"${PROJECT_SOURCE_DIR}/src/*.c"
"${PROJECT_SOURCE_DIR}/src/*.h"
"${PROJECT_SOURCE_DIR}/main.c")

#添加宏定义
add_definitions()

add_executable(${CMAKE_PROJECT_NAME} ${SRC_FILES})
