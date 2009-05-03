#########################################################################
# libdontpanic section
#########################################################################
set(libdontpanic_SRCS
    action.cpp
    action_template.cpp
    collaboration_type.cpp
    project.cpp
    task.cpp
   )

kde4_add_library(dontpanic SHARED ${libdontpanic_SRCS})
target_link_libraries(dontpanic ${KDE4_KDECORE_LIBS})

install(TARGETS dontpanic DESTINATION ${PLUGIN_INSTALL_DIR})