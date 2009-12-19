#########################################################################
# PRIVATE SECTION
#########################################################################
set(dontpanikpart_LIB_SRCS
    kprojectstablemodel.cpp
    kprojectstable.cpp
    kactionstablemodel.cpp
    kactionstable.cpp
    kprojectsdialog.cpp
    kmainwidget.cpp
    dont_panik_part_core.cpp
   )

set(dontpanikpart_LIB_UIS
    ui/kmainwidget.ui
    ui/kprojectsdialog.ui
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
#########################################################################
# KPART SECTION
#########################################################################
#kde_module_LTLIBRARIES = libdontpanicpart.la
set(dontpanik_PART_SRCS
   dontpanik_part.cpp
 )

kde4_add_plugin(dontpanikpart ${dontpanik_PART_SRCS})

target_link_libraries(dontpanikpart ${KDE4_KDEUI_LIBS} dontpanikpartprivate ${KDE4_KPARTS_LIBS} )

install( FILES dontpanik_part.desktop  DESTINATION ${XDG_APPS_INSTALL_DIR} )
install( FILES dontpanik_part.rc  DESTINATION  ${DATA_INSTALL_DIR}/dontpanikpart )

install(TARGETS dontpanikpart  DESTINATION ${PLUGIN_INSTALL_DIR} )


##########Application Shell#############
set(dontpanik_SRCS
   main.cpp
   dontpanik.cpp
 )

kde4_add_executable(dontpanik_bin ${dontpanik_SRCS})

target_link_libraries(dontpanik_bin ${KDE4_KDEUI_LIBS} ${KDE4_KPARTS_LIBS})
set_target_properties(dontpanik_bin PROPERTIES OUTPUT_NAME dontpanik)


########### install files ###############
install(TARGETS dontpanik_bin ${INSTALL_TARGETS_DEFAULT_ARGS} )
install( FILES dontpanik.desktop  DESTINATION  ${XDG_APPS_INSTALL_DIR} )
install( FILES dontpanik_shell.rc  DESTINATION  ${DATA_INSTALL_DIR}/dontpanik )

 
