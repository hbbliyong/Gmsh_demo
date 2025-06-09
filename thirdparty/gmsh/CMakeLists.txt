cmake_minimum_required(VERSION 3.10)

# 定义库目标
add_library(gmsh INTERFACE)

# 设置包含目录
target_include_directories(gmsh INTERFACE
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

# 为父项目提供 DLL 路径变量
set(GMSH_DLL_PATH "${CMAKE_CURRENT_SOURCE_DIR}/lib/gmsh-4.13.dll" CACHE INTERNAL "Path to Gmsh DLL")
set(GMSH_LIB_PATH "${CMAKE_CURRENT_SOURCE_DIR}/lib/gmsh.lib" CACHE INTERNAL "Path to Gmsh LIB")

# 平台特定的设置
if(WIN32)
    # Windows: 链接 .lib 文件
    target_link_libraries(gmsh INTERFACE "${GMSH_LIB_PATH}")

    # 标记 DLL 需要复制 (给父项目使用)
    set_property(TARGET gmsh APPEND PROPERTY COPY_FILES "${GMSH_DLL_PATH}")
else()
    # Unix-like: 直接链接共享库
    if(APPLE)
        set(GMSH_LIB "${CMAKE_CURRENT_SOURCE_DIR}/lib/libgmsh.dylib")
    else()
        set(GMSH_LIB "${CMAKE_CURRENT_SOURCE_DIR}/lib/libgmsh.so")
    endif()

    target_link_libraries(gmsh INTERFACE "${GMSH_LIB}")
endif()

# 创建命名空间别名目标
add_library(gmsh::gmsh ALIAS gmsh)

# 定义复制 DLL 的函数
function(copy_gmsh_dll target)
    if(WIN32 AND EXISTS "${GMSH_DLL_PATH}")
        add_custom_command(TARGET ${target} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${GMSH_DLL_PATH}"
                "$<TARGET_FILE_DIR:${target}>"
                COMMENT "Copying Gmsh DLL to runtime directory"
        )
    endif()
endfunction()