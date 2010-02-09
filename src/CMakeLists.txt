set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

add_subdirectory(libs)
add_subdirectory(dontpanic)
if(DP_BUILD_KONTACT_PLUGIN)
  add_subdirectory(dontpanik)
endif(DP_BUILD_KONTACT_PLUGIN)
add_subdirectory(tiptools)
