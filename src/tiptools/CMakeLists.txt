set(TIP_SRC main.cpp)


kde4_add_executable(dp_tipimport ${TIP_SRC})
target_link_libraries(dp_tipimport ${KDE4_KDEUI_LIBS})

install(TARGETS dp_tipimport ${INSTALL_TARGETS_DEFAULT_ARGS} )