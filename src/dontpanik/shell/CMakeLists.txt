##########Application Shell#############
set(dontpanik_SRCS
   main.cpp
   dontpanik.cpp
 )

add_executable(dontpanik_bin ${dontpanik_SRCS})

target_link_libraries(dontpanik_bin KF5::Parts KF5::XmlGui)
set_target_properties(dontpanik_bin PROPERTIES OUTPUT_NAME dontpanik)


########### install files ###############
install(TARGETS dontpanik_bin ${INSTALL_TARGETS_DEFAULT_ARGS} )
install( FILES dontpanik.desktop  DESTINATION  ${XDG_APPS_INSTALL_DIR} )
install( FILES dontpanik_shell.rc  DESTINATION  ${KXMLGUI_INSTALL_DIR}/dontpanik )

