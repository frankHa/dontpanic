include_directories(
   ${CMAKE_BINARY_DIR}
   )
 
# We add our source code here
set(plasma_dp_SRCS 
    actionitem.cpp
    dialog.cpp
    plasma-dontpanic.cpp
    detail/actiontemplateaction.cpp
    detail/actiondescription.cpp
    )
 
# Now make sure all files get to the right place
add_library(plasma_applet_dontpanic ${plasma_dp_SRCS})
target_link_libraries(plasma_applet_dontpanic 
                      KF5::Plasma dontpanic_lib dontpanic_client_lib)
 
install(TARGETS plasma_applet_dontpanic
        DESTINATION ${PLUGIN_INSTALL_DIR})
 
install(FILES plasma-applet-dontpanic.desktop
        DESTINATION ${SERVICES_INSTALL_DIR})
