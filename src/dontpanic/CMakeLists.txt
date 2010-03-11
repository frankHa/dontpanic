include(DBusMacros)

########################################################################
# we are using sqlite as storage backend:
########################################################################
find_package(Sqlite REQUIRED)
include_directories(${SQLITE_INCLUDE_DIR})
add_definitions(${SQLITE_DEFINITIONS})


include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(dontpanic_SRCS 
    actiontemplatemanager.cpp
    application.cpp
    context.cpp
    dbus.cpp
    main.cpp
    persistencebackend.cpp
    plannedworkingtimemanager.cpp
    projectmanager.cpp
    reportmanager.cpp
    taskmanager.cpp
    timetracker.cpp
    persistence/sqlite.cpp
    persistence/sqlite/action.cpp
    persistence/sqlite/actiontemplate.cpp
    persistence/sqlite/project.cpp
    persistence/sqlite/task.cpp    
    persistence/sqlite/worktimeperday.cpp
    reports/cfreport.cpp
    reports/plannedworkingtime.cpp
   )

qt4_add_dbus_adaptor(dontpanic_SRCS  
                    ${DBUS_INTERFACES_PATH}/org.dontpanic.TimeTracker.xml
                    timetracker.h dp::TimeTracker)

qt4_add_dbus_adaptor(dontpanic_SRCS
                    ${DBUS_INTERFACES_PATH}/org.dontpanic.ProjectManager.xml
                    projectmanager.h dp::ProjectManager)
qt4_add_dbus_adaptor(dontpanic_SRCS
                    ${DBUS_INTERFACES_PATH}/org.dontpanic.ReportManager.xml
                    reportmanager.h dp::ReportManager)
qt4_add_dbus_adaptor(dontpanic_SRCS
                    ${DBUS_INTERFACES_PATH}/org.dontpanic.TaskManager.xml
                    taskmanager.h dp::TaskManager)
qt4_add_dbus_adaptor(dontpanic_SRCS
                    ${DBUS_INTERFACES_PATH}/org.dontpanic.ActionTemplateManager.xml
                    actiontemplatemanager.h dp::ActionTemplateManager)

qt4_add_dbus_adaptor(dontpanic_SRCS
                    ${DBUS_INTERFACES_PATH}/org.dontpanic.PlannedWorkingTimeManager.xml
                    plannedworkingtimemanager.h dp::PlannedWorkingTimeManager)

kde4_add_executable(dontpanic ${dontpanic_SRCS})
target_link_libraries(dontpanic ${libuuid_LIB} dontpanic_lib ${QT_QTCORE_LIBRARY} ${QT_QTDBUS_LIBRARY} ${QT_QTSQL_LIBRARY})
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