
STRING(COMPARE EQUAL "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_BINARY_DIR}" _insource)

IF(_insource)
  MESSAGE(FATAL_ERROR "Please don't use CMake within the source directory")
ENDIF(_insource)