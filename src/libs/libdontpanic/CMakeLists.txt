#########################################################################
# libdontpanic section
#########################################################################

  

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.h.in ${CMAKE_CURRENT_BINARY_DIR}/libdontpanic/config.h)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(libdontpanic_SRCS 
    action.cpp
    actiontemplate.cpp
    collaborationtype.cpp
    dbus.cpp
    leavetype.cpp
    project.cpp
    reportdata.cpp
    reportdatafilter.cpp
    reporttype.cpp
    report.cpp 
    task.cpp
    time.cpp
    timerange.cpp 
    timerangeformatter.cpp 
    uuid.cpp
    worktimeperday.cpp
    dbus_support/action.cpp
    dbus_support/actiontemplate.cpp
    dbus_support/project.cpp
    dbus_support/report.cpp
    dbus_support/reportdata.cpp
    dbus_support/reportdatafilter.cpp
    dbus_support/reporttype.cpp
    dbus_support/task.cpp
    dbus_support/timerange.cpp
    dbus_support/qdatetime.cpp
    dbus_support/uuid.cpp    
    dbus_support/worktimeperday.cpp
   )

kde4_add_library(dontpanic_lib SHARED ${libdontpanic_SRCS})
target_link_libraries(dontpanic_lib ${KDE4_KDECORE_LIBS} ${SQLITE_LIBRARIES} ${libuuid_LIB})
set_target_properties(dontpanic_lib PROPERTIES OUTPUT_NAME dontpanic)

install(TARGETS dontpanic_lib DESTINATION ${LIB_INSTALL_DIR})