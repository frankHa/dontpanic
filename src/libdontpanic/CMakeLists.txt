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
    leave_type.cpp
    project.cpp
    task.cpp
   )
#TODO add support for leave types!

kde4_add_library(dontpanic SHARED ${libdontpanic_SRCS})
target_link_libraries(dontpanic ${KDE4_KDECORE_LIBS} ${SQLITE_LIBRARIES})

install(TARGETS dontpanic DESTINATION ${PLUGIN_INSTALL_DIR})