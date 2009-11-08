PROJECT(TIPIMPORT CXX)
set(TIP_SRC application.cpp main.cpp)

qt4_add_dbus_interface_with_includes(TIP_SRC
                                    ${DBUS_INTERFACES_PATH}/org.dontpanic.ProjectManager.xml
                                    projectmanager
                                    libdontpanic/dbus_support/project.hpp
                                    libdontpanic/dbus_support/quuid.h
                                    )

kde4_add_executable(dp_tipimport ${TIP_SRC})
target_link_libraries(dp_tipimport ${KDE4_KDEUI_LIBS} dontpanic_lib)



install(TARGETS dp_tipimport ${INSTALL_TARGETS_DEFAULT_ARGS} )