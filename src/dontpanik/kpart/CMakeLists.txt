add_subdirectory(core)
include_directories(core ${CMAKE_BINARY_DIR})

#########################################################################
# KPART SECTION
#########################################################################
#kde_module_LTLIBRARIES = libdontpanicpart.la
set(dontpanik_PART_SRCS
   dontpanik_part.cpp
 )

configure_file(config.h.cmake ${CMAKE_BINARY_DIR}/config.h)

add_library(dontpanikpart MODULE ${dontpanik_PART_SRCS})

target_link_libraries(dontpanikpart dontpanikpartprivate dontpanic_lib  KF5::IconThemes)

install( FILES dontpanik_part.desktop  DESTINATION ${XDG_APPS_INSTALL_DIR} )
install( FILES dontpanik_part.rc  DESTINATION  ${CMAKE_INSTALL_KXMLGUI5DIR}/dontpanik )
install( FILES dontpanikpart.notifyrc  DESTINATION  ${CMAKE_INSTALL_KNOTIFY5RCDIR} )

#install(TARGETS dontpanikpart  DESTINATION ${CMAKE_INSTALL_LIBDIR}/qt5/plugins/ )
install(TARGETS dontpanikpart  DESTINATION ${QT_PLUGIN_INSTALL_DIR} )

