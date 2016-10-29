ADD_EXECUTABLE(test_direct_access test_direct_access.c)
TARGET_LINK_LIBRARIES(test_direct_access tlpi_lib)

ADD_EXECUTABLE(direct_read direct_read.c)
TARGET_LINK_LIBRARIES(direct_read tlpi_lib)

ADD_EXECUTABLE(tail tail.c)
TARGET_LINK_LIBRARIES(tail tlpi_lib)
