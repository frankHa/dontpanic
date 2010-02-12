include_directories(
   ${CMAKE_BINARY_DIR}
   )
 
# We add our source code here
set(dontpanic_engine_SRCS dontpanicengine.cpp)
 
# Now make sure all files get to the right place
kde4_add_plugin(plasma_engine_dontpanic ${dontpanic_engine_SRCS})
target_link_libraries(plasma_engine_dontpanic
                      ${KDE4_KDECORE_LIBS}
                      ${KDE4_PLASMA_LIBS}
                      dontpanic_client_lib)
 
install(TARGETS plasma_engine_dontpanic
        DESTINATION ${PLUGIN_INSTALL_DIR})
 
install(FILES plasma-engine-dontpanic.desktop
        DESTINATION ${SERVICES_INSTALL_DIR})
