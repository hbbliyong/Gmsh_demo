cmake_minimum_required(VERSION 3.31)
project(GmeshDemo)

set(CMAKE_CXX_STANDARD 20)
file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.*)
add_executable(GmeshDemo ${SOURCES})

add_subdirectory(thirdparty/gmsh)
# 链接gmsh库
target_link_libraries(${PROJECT_NAME} PRIVATE gmsh::gmsh)

# 如果使用动态库，在Windows下需要复制dll到可执行文件目录
# 复制 Gmsh DLL 到运行目录
copy_gmsh_dll(${PROJECT_NAME})