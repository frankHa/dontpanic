add_subdirectory(core)

set(dontpanic_SRCS 
    main.cpp    
   )

add_executable(dontpanic ${dontpanic_SRCS})
target_link_libraries(dontpanic libdontpanic_core ${libuuid_LIB} dontpanic_lib)
install(TARGETS dontpanic ${INSTALL_TARGETS_DEFAULT_ARGS} )


if(DP_INSTALL_SYSTEM_FILES)
  dbus_add_activation_service(org.dontpanic.service.in)
  install( FILES
           ${DBUS_INTERFACES_PATH}/org.dontpanic.ActionTemplateManager.xml
           ${DBUS_INTERFACES_PATH}/org.dontpanic.TimeTracker.xml
           ${DBUS_INTERFACES_PATH}/org.dontpanic.ProjectManager.xml
	   ${DBUS_INTERFACES_PATH}/org.dontpanic.TaskManager.xml
           DESTINATION
           ${KDE4_DBUS_INTERFACES_DIR} 
           )
else(DP_INSTALL_SYSTEM_FILES)
    message(STATUS "******************************************************")
    message(STATUS "Skipping the installation of system wide needed files,")
    message(STATUS "such as DBUS interface and service definitions.")
    message(STATUS "If you are not completely sure, what you are doing")
    message(STATUS "please consider setting DP_INSTALL_SYSTEM_FILES to ON")
    message(STATUS "and perform the installation with root access")
    message(STATUS "******************************************************")
endif (DP_INSTALL_SYSTEM_FILES)