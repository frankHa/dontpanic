find_package(KdepimLibs REQUIRED)
find_package(Akonadi REQUIRED)

include_directories(../include)

set( dontpanicresource_SRCS
dontpanicresource.cpp
)

install( FILES dontpanicresource.desktop DESTINATION "${AKONADI_SHARE_DIR}/akonadi/agents" )

#kde4_add_ui_files(icalresource_SRCS ${AKONADI_SINGLEFILERESOURCE_SHARED_UI})
#kde4_add_kcfg_files(icalresource_SRCS settings.kcfgc)
#kcfg_generate_dbus_interface(${CMAKE_CURRENT_SOURCE_DIR}/icalresource.kcfg org.kde.Akonadi.ICal.Settings)
#qt4_add_dbus_adaptor(icalresource_SRCS
#${CMAKE_CURRENT_BINARY_DIR}/org.kde.Akonadi.ICal.Settings.xml settings.h Settings
#)

kde4_add_executable(akonadi_dontpanic_resource ${dontpanicresource_SRCS})

target_link_libraries(akonadi_dontpanic_resource ${KDEPIMLIBS_AKONADI_LIBS} dontpanic_client_lib)

install(TARGETS akonadi_dontpanic_resource ${INSTALL_TARGETS_DEFAULT_ARGS})
