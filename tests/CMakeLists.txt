add_executable(test test.c printer.c)

link_directories(${C-structures}/src)

target_link_libraries(test mlib cgreen)

INCLUDE_DIRECTORIES(${C-structures_SOURCE_DIR}/src) 
