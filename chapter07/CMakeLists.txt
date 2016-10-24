INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/lib)

ADD_EXECUTABLE(free_and_sbrk free_and_sbrk.c)
TARGET_LINK_LIBRARIES(free_and_sbrk tlpi_lib)

