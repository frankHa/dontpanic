project(dontpanic)
find_package(Boost REQUIRED)
find_package(KDE4 REQUIRED)
include (KDE4Defaults)

include_directories( ${KDE4_INCLUDES} ${QT_INCLUDES} )
include_directories(${CMAKE_SOURCE_DIR}/src)

add_subdirectory( doc )
add_subdirectory( src )
add_subdirectory( icons )
