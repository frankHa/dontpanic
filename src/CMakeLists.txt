#########################################################################
# KPART SECTION
#########################################################################
#kde_module_LTLIBRARIES = libdontpanicpart.la
set(dontpanic_PART_SRCS
   dontpanic_part.cpp
 )

kde4_add_plugin(dontpanicpart WITH_PREFIX ${dontpanic_PART_SRCS})

target_link_libraries(dontpanicpart ${KDE4_KDEUI_LIBS} ${KDE4_KPARTS_LIBS} )

install( FILES dontpanic_part.desktop  DESTINATION ${XDG_APPS_INSTALL_DIR} )
install( FILES dontpanic_part.rc  DESTINATION  ${DATA_INSTALL_DIR}/dontpanicpart )

install(TARGETS dontpanicpart  DESTINATION ${PLUGIN_INSTALL_DIR} )


##########Application Shell#############
set(dontpanic_SRCS
   main.cpp
   dontpanic.cpp
 )

kde4_add_executable(dontpanic ${dontpanic_SRCS})

target_link_libraries(dontpanic ${KDE4_KDEUI_LIBS} ${KDE4_KPARTS_LIBS})

########### install files ###############
install(TARGETS dontpanic ${INSTALL_TARGETS_DEFAULT_ARGS} )
install( FILES dontpanic.desktop  DESTINATION  ${XDG_APPS_INSTALL_DIR} )
install( FILES dontpanic_shell.rc  DESTINATION  ${DATA_INSTALL_DIR}/dontpanic )

add_subdirectory(libdontpanic)
add_subdirectory(dontpanicpart)
