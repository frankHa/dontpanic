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

kde4_add_plugin(dontpanikpart ${dontpanik_PART_SRCS})

target_link_libraries(dontpanikpart ${KDE4_KDEUI_LIBS} dontpanikpartprivate dontpanic_lib ${KDE4_KPARTS_LIBS} )

install( FILES dontpanik_part.desktop  DESTINATION ${XDG_APPS_INSTALL_DIR} )
install( FILES dontpanik_part.rc  DESTINATION  ${DATA_INSTALL_DIR}/dontpanikpart )

install(TARGETS dontpanikpart  DESTINATION ${PLUGIN_INSTALL_DIR} )

