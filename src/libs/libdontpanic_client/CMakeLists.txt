#########################################################################
# libdontpanic section
#########################################################################
include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(libdontpanic_client_SRCS
    projectmanager.cpp
   )

qt4_wrap_cpp(libdontpanic_client_SRCS
             ../../include/libdontpanic_client/projectmanager.h
             )

qt4_add_dbus_interface_with_includes(libdontpanic_client_SRCS
                                    ${DBUS_INTERFACES_PATH}/org.dontpanic.TimeTracker.xml
                                    remote_timetracker
                                    libdontpanic/dbus_support/quuid.h
                                    )

qt4_add_dbus_interface_with_includes(libdontpanic_client_SRCS
                                    ${DBUS_INTERFACES_PATH}/org.dontpanic.ProjectManager.xml
                                    remote_projectmanager
                                    libdontpanic/dbus_support/project.hpp
                                    libdontpanic/dbus_support/quuid.h
                                    )

qt4_add_dbus_interface_with_includes(libdontpanic_client_SRCS
                                    ${DBUS_INTERFACES_PATH}/org.dontpanic.TaskManager.xml
                                    remote_taskmanager
                                    libdontpanic/dbus_support/task.hpp
                                    libdontpanic/dbus_support/quuid.h
                                    )

kde4_add_library(dontpanic_client_lib STATIC ${libdontpanic_client_SRCS})
target_link_libraries(dontpanic_client_lib ${KDE4_KDECORE_LIBS} dontpanic_lib)
set_target_properties(dontpanic_client_lib PROPERTIES OUTPUT_NAME dontpanic_client)

install(TARGETS dontpanic_client_lib DESTINATION ${PLUGIN_INSTALL_DIR})