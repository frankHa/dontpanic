#########################################################################
# libdontpanic section
#########################################################################
include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(libdontpanic_client_SRCS 
    actionscache.cpp
    actiontemplatemanager.cpp
    projectmanager.cpp
    plannedworkingtimemanager.cpp
    reportmanager.cpp
    taskmanager.cpp
    timetracker.cpp
   )

qt5_wrap_cpp(libdontpanic_client_SRCS
          ../../include/libdontpanic_client/actionscache.h
	     ../../include/libdontpanic_client/actiontemplatemanager.h
         ../../include/libdontpanic_client/projectmanager.h
         ../../include/libdontpanic_client/plannedworkingtimemanager.h
         ../../include/libdontpanic_client/reportmanager.h
	     ../../include/libdontpanic_client/taskmanager.h
	     ../../include/libdontpanic_client/timetracker.h
             )

qt5_add_dbus_interface_with_includes(libdontpanic_client_SRCS
                                    ${DBUS_INTERFACES_PATH}/org.dontpanic.TimeTracker.xml
                                    remote_timetracker
                                    libdontpanic/dbus_support/action.hpp
                                    libdontpanic/dbus_support/actiontemplate.hpp
                                    libdontpanic/dbus_support/qdatetime.h
                                    libdontpanic/dbus_support/uuid.h
                                    )

qt5_add_dbus_interface_with_includes(libdontpanic_client_SRCS
                                    ${DBUS_INTERFACES_PATH}/org.dontpanic.ProjectManager.xml
                                    remote_projectmanager
                                    libdontpanic/dbus_support/project.hpp
                                    libdontpanic/dbus_support/uuid.h
                                    )
qt5_add_dbus_interface_with_includes(libdontpanic_client_SRCS
                                    ${DBUS_INTERFACES_PATH}/org.dontpanic.ReportManager.xml
                                    remote_reportmanager
                                    libdontpanic/dbus_support/report.h
                                    libdontpanic/dbus_support/reporttype.h
                                    libdontpanic/dbus_support/timerange.h
                                    libdontpanic/dbus_support/uuid.h
                                    )
qt5_add_dbus_interface_with_includes(libdontpanic_client_SRCS
                                    ${DBUS_INTERFACES_PATH}/org.dontpanic.TaskManager.xml
                                    remote_taskmanager
                                    libdontpanic/dbus_support/task.hpp
                                    libdontpanic/dbus_support/uuid.h
                                    )
qt5_add_dbus_interface_with_includes(libdontpanic_client_SRCS
                                    ${DBUS_INTERFACES_PATH}/org.dontpanic.ActionTemplateManager.xml
                                    remote_action_template_manager
                                    libdontpanic/dbus_support/actiontemplate.hpp
                                    libdontpanic/dbus_support/uuid.h
                                    )
                                   
qt5_add_dbus_interface_with_includes(libdontpanic_client_SRCS
                                   ${DBUS_INTERFACES_PATH}/org.dontpanic.PlannedWorkingTimeManager.xml
                                  remote_planned_working_time_manager
                                   libdontpanic/dbus_support/worktimeperday.h
                                   )

#add_definitions(-fPIC)
add_library(dontpanic_client_lib SHARED ${libdontpanic_client_SRCS})
target_link_libraries(dontpanic_client_lib dontpanic_lib)
set_target_properties(dontpanic_client_lib PROPERTIES OUTPUT_NAME dontpanic_client)
install(TARGETS dontpanic_client_lib DESTINATION ${LIB_INSTALL_DIR})