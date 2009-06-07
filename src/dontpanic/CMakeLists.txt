include(DBusMacros)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(dontpanic_SRCS
    Application.cpp
    DBus.cpp
    main.cpp
    PersistanceBackend.cpp
    PersistanceBackendDBusWrapper.cpp
    persistance/Sqlite.cpp
    persistance/sqlite/Project.cpp
   )

qt4_generate_dbus_interface(Application.hpp org.dontpanic.Application.xml)
qt4_add_dbus_adaptor(dontpanic_SRCS ${CMAKE_CURRENT_BINARY_DIR}/org.dontpanic.Application.xml Application.hpp Application)

# needs to be defined by hand due to using a customized parameter type
#qt4_generate_dbus_interface(PersistanceBackendDBusWrapper.hpp org.dontpanic.Persistance.xml)
qt4_add_dbus_adaptor(dontpanic_SRCS interfaces/org.dontpanic.Persistance.xml PersistanceBackendDBusWrapper.hpp dp::PersistanceBackendDBusWrapper)

kde4_add_executable(dontpanic ${dontpanic_SRCS})
target_link_libraries(dontpanic dontpanic_lib ${QT_QTCORE_LIBRARY} ${QT_QTDBUS_LIBRARY} ${QT_QTSQL_LIBRARY})
install(TARGETS dontpanic ${INSTALL_TARGETS_DEFAULT_ARGS} )


if(DP_INSTALL_SYSTEM_FILES)
  dbus_add_activation_service(org.dontpanic.service.in)
  install( FILES
           ${CMAKE_CURRENT_BINARY_DIR}/org.dontpanic.Application.xml
           interfaces/org.dontpanic.Persistance.xml
           DESTINATION
           ${KDE4_DBUS_INTERFACES_DIR} 
           )
else(DP_INSTALL_SYSTEM_FILES)
    message(STATUS "******************************************************")
    message(STATUS "Skipping the installation of system wide needed files,")
    message(STATUS "such as DBUS interface and service definitions.")
    message(STATUS "If you are not completely sure, what you are doing")
    message(STATUS "please consider setting DP_INSTALL_SYSTEM_FILES to ON")
    message(STATUS "and perform the installation with root access")
    message(STATUS "******************************************************")
endif (DP_INSTALL_SYSTEM_FILES)
add_subdirectory(interfaces)