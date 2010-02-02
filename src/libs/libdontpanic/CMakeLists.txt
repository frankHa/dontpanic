#########################################################################
# libdontpanic section
#########################################################################
set(libdontpanic_SRCS 
    action.cpp
    actiontemplate.cpp
    collaborationtype.cpp
    dbus.cpp
    durationformatter.cpp 
    leavetype.cpp
    project.cpp
    report.cpp 
    task.cpp
    timerange.cpp 
    dbus_support/action.cpp
    dbus_support/actiontemplate.cpp
    dbus_support/project.cpp
    dbus_support/report.cpp
    dbus_support/task.cpp
    dbus_support/timerange.cpp
    dbus_support/qdatetime.cpp
    dbus_support/quuid.cpp    
   )

add_definitions(-fPIC)
kde4_add_library(dontpanic_lib STATIC ${libdontpanic_SRCS})
target_link_libraries(dontpanic_lib ${KDE4_KDECORE_LIBS} ${SQLITE_LIBRARIES})
set_target_properties(dontpanic_lib PROPERTIES OUTPUT_NAME dontpanic)

install(TARGETS dontpanic_lib DESTINATION ${PLUGIN_INSTALL_DIR})