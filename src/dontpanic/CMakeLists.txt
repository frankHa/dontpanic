add_subdirectory(core)

set(dontpanic_SRCS 
    main.cpp    
   )

add_executable(dontpanic ${dontpanic_SRCS})
target_link_libraries(dontpanic libdontpanic_core ${libuuid_LIB} dontpanic_lib)
install(TARGETS dontpanic ${INSTALL_TARGETS_DEFAULT_ARGS} )


  dbus_add_activation_service(org.dontpanic.service.in)
  install( FILES
           ${DBUS_INTERFACES_PATH}/org.dontpanic.ActionTemplateManager.xml
           ${DBUS_INTERFACES_PATH}/org.dontpanic.TimeTracker.xml
           ${DBUS_INTERFACES_PATH}/org.dontpanic.ProjectManager.xml
	   ${DBUS_INTERFACES_PATH}/org.dontpanic.TaskManager.xml
           DESTINATION
           ${KDE_INSTALL_DBUSINTERFACEDIR} 
           )