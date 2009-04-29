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
