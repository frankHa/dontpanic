include_directories(
   ${CMAKE_BINARY_DIR}
   )
 
# We add our source code here
set(dontpanic_engine_SRCS 
    dontpanicaction.cpp
    dontpanicengine.cpp
    dontpanicservice.cpp
)
 
# Now make sure all files get to the right place
add_library(plasma_engine_dontpanic MODULE ${dontpanic_engine_SRCS})
target_link_libraries(plasma_engine_dontpanic
                      KF5::ConfigCore KF5::CoreAddons KF5::Plasma
                      dontpanic_lib dontpanic_client_lib)

kcoreaddons_desktop_to_json(plasma_engine_dontpanic plasma-dataengine-dontpanic.desktop)

install(TARGETS plasma_engine_dontpanic
        DESTINATION ${PLUGIN_INSTALL_DIR}/plasma/dataengine)
 
install(FILES plasma-dataengine-dontpanic.desktop
        DESTINATION ${SERVICES_INSTALL_DIR})
install(FILES dontpanic.operations DESTINATION ${PLASMA_DATA_INSTALL_DIR}/services)