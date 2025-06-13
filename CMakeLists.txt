cmake_minimum_required(VERSION 3.31)
project(GmeshDemo)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(thirdparty/gmsh)

#add_subdirectory("source/01_2D_Model")
#add_subdirectory("source/03_BooleanOperation")
#add_subdirectory(source/04_Generate)
add_subdirectory(source/05_GetNode)