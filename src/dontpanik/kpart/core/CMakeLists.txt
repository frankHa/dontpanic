#########################################################################
# PRIVATE SECTION
#########################################################################
set(dontpanikpart_LIB_SRCS 
    kprojectstablemodel.cpp
    kprojectstable.cpp
    kactionstablemodel.cpp
    kactionstable.cpp
    kprojectsdialog.cpp
    kdayview.cpp
    kmainwidget.cpp
    kworktypesdialog.cpp
    kworktypestable.cpp
    kworktypestablemodel.cpp
    dont_panik_part_core.cpp
   )

set(dontpanikpart_LIB_UIS
    ui/kdayview.ui
    ui/kprojectsdialog.ui
    ui/kworktypesdialog.ui
   )

qt4_wrap_ui(dontpanikpart_LIB_SRCS ${dontpanikpart_LIB_UIS})

qt4_add_dbus_interface_with_includes(dontpanikpart_LIB_SRCS 
                                    ${DBUS_INTERFACES_PATH}/org.dontpanic.TimeTracker.xml
                                    timetracker
                                    libdontpanic/dbus_support/quuid.h
                                    )

qt4_add_dbus_interface_with_includes(dontpanikpart_LIB_SRCS
                                    ${DBUS_INTERFACES_PATH}/org.dontpanic.ProjectManager.xml
                                    projectmanager
                                    libdontpanic/dbus_support/project.hpp
                                    libdontpanic/dbus_support/quuid.h
                                    )

kde4_add_library(dontpanikpartprivate SHARED ${dontpanikpart_LIB_SRCS})
target_link_libraries(dontpanikpartprivate ${KDE4_KDEUI_LIBS} dontpanic_lib)
install(TARGETS dontpanikpartprivate ${INSTALL_TARGETS_DEFAULT_ARGS} LIBRARY NAMELINK_SKIP)

