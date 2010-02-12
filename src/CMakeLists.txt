set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

add_subdirectory(libs)
add_subdirectory(dontpanic)
if(DP_BUILD_PLASMA_COMPONENT)
 add_subdirectory(plasma)
endif (DP_BUILD_PLASMA_COMPONENT)
add_subdirectory(dontpanik)
add_subdirectory(tiptools)
