INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/lib)

ADD_EXECUTABLE(t_time t_time.c)
TARGET_LINK_LIBRARIES(t_time tlpi_lib)

ADD_EXECUTABLE(calendar_time calendar_time.c)
TARGET_LINK_LIBRARIES(calendar_time tlpi_lib)

ADD_EXECUTABLE(show_time show_time.c)
TARGET_LINK_LIBRARIES(show_time tlpi_lib)




