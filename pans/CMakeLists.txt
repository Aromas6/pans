file(GLOB_RECURSE PANS_SOURCES CONFIGURE_DEPENDS *.cpp *.cc *.c)
file(GLOB_RECURSE PANS_HEADERS CONFIGURE_DEPENDS *.h *.hpp)

add_library(pans STATIC ${PANS_SOURCES})

target_include_directories(pans 
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> 
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}> 
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

#继承所有编译/链接选项
target_link_libraries(pans PUBLIC pans_options)

# 主库可能要求更严格的警告
target_compile_options(pans PRIVATE
    $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:
        -Werror     #将警告是为错误（主库严格要求）
        #-Wno-deprecated-declarations #如果确实需要，保留
    >
)

install(TARGETS pans 
    EXPORT pansTargets 
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} 
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} 
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(FILES ${PANS_HEADERS} 
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/pans
)