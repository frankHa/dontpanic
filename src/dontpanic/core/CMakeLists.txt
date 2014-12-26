include(DBusMacros)

########################################################################
# we are using sqlite as storage backend:
########################################################################
find_package(Sqlite3 REQUIRED)
include_directories(${SQLITE3_INCLUDE_DIRS})
add_definitions(${SQLITE3_DEFINITIONS})


include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(dontpanic_core_lib_SRCS 
    actiontemplatemanager.cpp
    application.cpp
    context.cpp
    dbus.cpp
    main.cpp
    persistencebackend.cpp
    plannedworkingtimemanager.cpp
    projectmanager.cpp
    reportmanager.cpp
    taskmanager.cpp
    timetracker.cpp
    persistence/persistenceengine.cpp
    persistence/sqlite.cpp
    persistence/sqlite/action.cpp
    persistence/sqlite/actiontemplate.cpp
    persistence/sqlite/currentholidayregion.cpp
    persistence/sqlite/project.cpp
    persistence/sqlite/reporttype.cpp
    persistence/sqlite/task.cpp    
    persistence/sqlite/transaction.cpp
    persistence/sqlite/worktimeperday.cpp
    reports/category.cpp
    reports/columns.cpp
    reports/filter.cpp
    reports/group.cpp
    reports/plannedworkingtime.cpp
    reports/reportgenerator.cpp
   )

qt5_add_dbus_adaptor(dontpanic_core_lib_SRCS  
                    ${DBUS_INTERFACES_PATH}/org.dontpanic.TimeTracker.xml
                    timetracker.h dp::TimeTracker)

qt5_add_dbus_adaptor(dontpanic_core_lib_SRCS
                    ${DBUS_INTERFACES_PATH}/org.dontpanic.ProjectManager.xml
                    projectmanager.h dp::ProjectManager)
qt5_add_dbus_adaptor(dontpanic_core_lib_SRCS
                    ${DBUS_INTERFACES_PATH}/org.dontpanic.ReportManager.xml
                    reportmanager.h dp::ReportManager)
qt5_add_dbus_adaptor(dontpanic_core_lib_SRCS
                    ${DBUS_INTERFACES_PATH}/org.dontpanic.TaskManager.xml
                    taskmanager.h dp::TaskManager)
qt5_add_dbus_adaptor(dontpanic_core_lib_SRCS
                    ${DBUS_INTERFACES_PATH}/org.dontpanic.ActionTemplateManager.xml
                    actiontemplatemanager.h dp::ActionTemplateManager)

qt5_add_dbus_adaptor(dontpanic_core_lib_SRCS
                    ${DBUS_INTERFACES_PATH}/org.dontpanic.PlannedWorkingTimeManager.xml
                    plannedworkingtimemanager.h dp::PlannedWorkingTimeManager)

add_library(libdontpanic_core STATIC ${dontpanic_core_lib_SRCS})
#target_link_libraries(libdontpanic_core ${libuuid_LIB} dontpanic_lib ${QT_QTCORE_LIBRARY} ${QT_QTDBUS_LIBRARY} ${QT_QTSQL_LIBRARY} ${KDEPIMLIBS_KHOLIDAYS_LIBS})
target_link_libraries(libdontpanic_core KF5::CoreAddons KF5::I18n Qt5::Core Qt5::DBus Qt5::Sql)
#install(TARGETS dontpanic ${INSTALL_TARGETS_DEFAULT_ARGS} )
