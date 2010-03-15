add_library(mlib SHARED mlib.h mheap.c mlib/mheap.h mstack.c mlib/mstack.h
    mlib/mlist.h mlist.c mlib/mstring.h mstring.c)

INCLUDE_DIRECTORIES(${C-structures_SOURCE_DIR}/src) 

FILE(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/mlib/*.h")

FILE(GLOB sources "${CMAKE_CURRENT_SOURCE_DIR}/*.c")

INSTALL(FILES ${headers} DESTINATION include/mlib)

INSTALL(FILES ${CMAKE_CURRENT_SOURCE_DIR}/mlib.h DESTINATION include)


INSTALL(TARGETS mlib 
    LIBRARY DESTINATION lib
    )
