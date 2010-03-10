add_library(structures heap.c heap.h stack.c stack.h)

add_executable(test test.c) 

target_link_libraries(test structures cgreen)
