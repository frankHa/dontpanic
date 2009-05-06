project(dontpanic)
find_package(Boost REQUIRED)
find_package(KDE4 REQUIRED)
include (KDE4Defaults)

option(DP_INSTALL_SYSTEM_FILES ON "Allows disabling the installation of files which needs root access and are rarely changed")

include_directories( ${KDE4_INCLUDES} ${QT_INCLUDES} )
include_directories(${CMAKE_SOURCE_DIR}/src)

add_subdirectory( doc )
add_subdirectory( src )
add_subdirectory( icons )
