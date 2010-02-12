include_directories(
   ${CMAKE_BINARY_DIR}
   )
 
# We add our source code here
set(plasma_dp_SRCS plasma-dontpanic.cpp)
 
# Now make sure all files get to the right place
kde4_add_plugin(plasma_applet_dontpanic ${plasma_dp_SRCS})
target_link_libraries(plasma_applet_dontpanic 
                      ${KDE4_PLASMA_LIBS} ${KDE4_KDEUI_LIBS})
 
install(TARGETS plasma_applet_dontpanic
        DESTINATION ${PLUGIN_INSTALL_DIR})
 
install(FILES plasma-applet-dontpanic.desktop
        DESTINATION ${SERVICES_INSTALL_DIR})
