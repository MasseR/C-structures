add_library(mlib SHARED mheap.c mheap.h mstack.c mstack.h mlist.h mlist.c mstring.h mstring.c)

FILE(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

INSTALL(FILES ${headers} DESTINATION include)

INSTALL(TARGETS mlib 
    LIBRARY DESTINATION lib
    )
