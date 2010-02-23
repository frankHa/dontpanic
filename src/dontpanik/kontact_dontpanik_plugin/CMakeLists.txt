find_package(KdepimLibs REQUIRED)

include_directories(../kpart)

set(kontact_dontpanik_PART_SRCS dontpanik_plugin.cpp)

kde4_add_plugin(kontact_dontpanik_plugin ${kontact_dontpanik_PART_SRCS})

target_link_libraries(kontact_dontpanik_plugin ${KDE4_KDEUI_LIBS} ${KDEPIMLIBS_KONTACTINTERFACE_LIBS})

install(TARGETS kontact_dontpanik_plugin  DESTINATION ${PLUGIN_INSTALL_DIR})

install(FILES dontpanik_plugin.desktop  DESTINATION ${SERVICES_INSTALL_DIR}/kontact)
