include_directories(../kpart)

set(kontact_dontpanik_PART_SRCS dontpanik_plugin.cpp)

add_library(kontact_dontpanik_plugin MODULE ${kontact_dontpanik_PART_SRCS})

target_link_libraries(kontact_dontpanik_plugin KF5::KontactInterface)

install(TARGETS kontact_dontpanik_plugin  DESTINATION ${KDE_INSTALL_PLUGINDIR})

install(FILES dontpanik_plugin.desktop  DESTINATION ${KDE_INSTALL_KSERVICES5DIR}/kontact)
