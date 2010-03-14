add_executable(test test.c)

link_directories(${C-structures}/src)

target_link_libraries(test mlib cgreen)
