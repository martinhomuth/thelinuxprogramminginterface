SET(library_sources
  error_functions.c
  get_num.c
)

INCLUDE_DIRECTORIES(${CMAKE_PROJECT_DIR}/include)
ADD_LIBRARY(tlpi_lib ${library_sources})



