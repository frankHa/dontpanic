#########################################################################
# libdontpanic section
#########################################################################
include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(libdontpanic_client_SRCS 
    actionscache.cpp
    actiontemplatemanager.cpp
    projectmanager.cpp
    reportmanager.cpp
    taskmanager.cpp
    timetracker.cpp
   )

qt4_wrap_cpp(libdontpanic_client_SRCS
	     ../../include/libdontpanic_client/actiontemplatemanager.h
         ../../include/libdontpanic_client/projectmanager.h
         ../../include/libdontpanic_client/reportmanager.h
	     ../../include/libdontpanic_client/taskmanager.h
	     ../../include/libdontpanic_client/timetracker.h
             )

qt4_add_dbus_interface_with_includes(libdontpanic_client_SRCS
                                    ${DBUS_INTERFACES_PATH}/org.dontpanic.TimeTracker.xml
                                    remote_timetracker
                                    libdontpanic/dbus_support/action.hpp
                                    libdontpanic/dbus_support/actiontemplate.hpp
                                    libdontpanic/dbus_support/qdatetime.h
                                    libdontpanic/dbus_support/uuid.h
                                    )

qt4_add_dbus_interface_with_includes(libdontpanic_client_SRCS
                                    ${DBUS_INTERFACES_PATH}/org.dontpanic.ProjectManager.xml
                                    remote_projectmanager
                                    libdontpanic/dbus_support/project.hpp
                                    libdontpanic/dbus_support/uuid.h
                                    )
qt4_add_dbus_interface_with_includes(libdontpanic_client_SRCS
                                    ${DBUS_INTERFACES_PATH}/org.dontpanic.ReportManager.xml
                                    remote_reportmanager
                                    libdontpanic/dbus_support/report.h
                                    libdontpanic/dbus_support/timerange.h
                                    )
qt4_add_dbus_interface_with_includes(libdontpanic_client_SRCS
                                    ${DBUS_INTERFACES_PATH}/org.dontpanic.TaskManager.xml
                                    remote_taskmanager
                                    libdontpanic/dbus_support/task.hpp
                                    libdontpanic/dbus_support/uuid.h
                                    )
qt4_add_dbus_interface_with_includes(libdontpanic_client_SRCS
                                    ${DBUS_INTERFACES_PATH}/org.dontpanic.ActionTemplateManager.xml
                                    remote_action_template_manager
                                    libdontpanic/dbus_support/actiontemplate.hpp
                                    libdontpanic/dbus_support/uuid.h
                                    )

add_definitions(-fPIC)
kde4_add_library(dontpanic_client_lib STATIC ${libdontpanic_client_SRCS})
target_link_libraries(dontpanic_client_lib ${KDE4_KDECORE_LIBS} dontpanic_lib)
set_target_properties(dontpanic_client_lib PROPERTIES OUTPUT_NAME dontpanic_client)

install(TARGETS dontpanic_client_lib DESTINATION ${PLUGIN_INSTALL_DIR})