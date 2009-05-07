########################################################################
# we are using sqlite as storage backend:
########################################################################
find_package(Sqlite REQUIRED)
include_directories(${SQLITE_INCLUDE_DIR})
add_definitions(${SQLITE_DEFINITIONS})


#########################################################################
# libdontpanic section
#########################################################################
set(libdontpanic_SRCS
    action.cpp
    action_template.cpp
    collaboration_type.cpp
    dbus.cpp
    leave_type.cpp
    project.cpp
    task.cpp
   )

kde4_add_library(dontpanic_lib SHARED ${libdontpanic_SRCS})
target_link_libraries(dontpanic_lib ${KDE4_KDECORE_LIBS} ${SQLITE_LIBRARIES})
set_target_properties(dontpanic_lib PROPERTIES OUTPUT_NAME dontpanic)

install(TARGETS dontpanic_lib DESTINATION ${PLUGIN_INSTALL_DIR})