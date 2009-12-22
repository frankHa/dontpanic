##########Application Shell#############
set(dontpanik_SRCS
   main.cpp
   dontpanik.cpp
 )

kde4_add_executable(dontpanik_bin ${dontpanik_SRCS})

target_link_libraries(dontpanik_bin ${KDE4_KDEUI_LIBS} ${KDE4_KPARTS_LIBS})
set_target_properties(dontpanik_bin PROPERTIES OUTPUT_NAME dontpanik)


########### install files ###############
install(TARGETS dontpanik_bin ${INSTALL_TARGETS_DEFAULT_ARGS} )
install( FILES dontpanik.desktop  DESTINATION  ${XDG_APPS_INSTALL_DIR} )
install( FILES dontpanik_shell.rc  DESTINATION  ${DATA_INSTALL_DIR}/dontpanik )

