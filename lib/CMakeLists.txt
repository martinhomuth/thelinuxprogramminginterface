SET(library_sources
  error_functions.c
  get_num.c
)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})
ADD_LIBRARY(tlpi_lib ${library_sources})



