include_directories(${CMAKE_BINARY_DIR})


set(dontpanikpart_LIB_SRCS 
    actiontemplateaction.cpp
    context.cpp 
    dayinfo.cpp 
    desktopnotificationmanager.cpp
    dont_panik_part_core.cpp
    editreporttypedialog.cpp
    kactiontemplateslist.cpp
    kactiontemplateslistmodel.cpp
    kcalendarwidget.cpp 
    kdurationstatusupdater.cpp 
    kprojectstablemodel.cpp
    kprojectstable.cpp
    kactionstableitemdelegate.cpp 
    kactionstablemodel.cpp
    kactionstablesortmodel.cpp 
    kactionstable.cpp
    keditactiondialog.cpp 
    keditactiontemplatedialog.cpp 
    keditprojectdialog.cpp
    kedittaskdialog.cpp
    #kholidayregioncombobox.cpp
    kprojectscombobox.cpp 
    kprojectsdialog.cpp
    kdayview.cpp
    kmainwidget.cpp
    kreporttable.cpp
    kreporttablemodel.cpp
    kreporttypeslist.cpp
    kreporttypeslistmodel.cpp
    kreportrangedialog.cpp 
    kreportview.cpp 
    kreportwidget.cpp 
    kstatus.cpp
    ktaskscombobox.cpp 
    ktasksdialog.cpp
    ktaskstable.cpp
    ktaskstablemodel.cpp    
    mailinterface.cpp 
    plannedworkingtimesdialog.cpp
    #reportexportedsuccessfullydialog.cpp
    selectprojectsdialog.cpp
    selecttasksdialog.cpp
    selectentitydialog.cpp
    selectentitydialogmodel.cpp
    selectentitytablemodel.cpp
    selectentitytablemodeladaptor.cpp
    statusnotifieritem.cpp
   )

set(dontpanikpart_LIB_UIS
    ui/editreporttypedialog.ui
    ui/kdayview.ui
    ui/keditactiondialog.ui    
    ui/keditactiontemplatedialog.ui
    ui/keditprojectdialog.ui
    ui/kedittaskdialog.ui
    ui/kprojectsdialog.ui
    ui/kreportrangedialog.ui
    ui/kreportview.ui
    ui/kreportwidget.ui
    ui/ktasksdialog.ui    
    ui/plannedworkingtimesdialog.ui
    ui/selectentitiesdialog.ui
   )
ki18n_wrap_ui(dontpanikpart_LIB_SRCS ${dontpanikpart_LIB_UIS})

set (KDEPIMLIBS_DBUS_INTERFACES_DIR "/usr/share/dbus-1/interfaces")
qt5_add_dbus_interface(dontpanikpart_LIB_SRCS
                       ${KDEPIMLIBS_DBUS_INTERFACES_DIR}/org.kde.kmail.kmail.xml
                       remote_kmail
)


add_library(dontpanikpartprivate SHARED ${dontpanikpart_LIB_SRCS})
target_link_libraries(dontpanikpartprivate KF5::ConfigCore KF5::IconThemes KF5::Notifications KF5::Parts KF5::XmlGui KF5::WidgetsAddons dontpanic_client_lib dontpanic_lib)
install(TARGETS dontpanikpartprivate ${INSTALL_TARGETS_DEFAULT_ARGS} LIBRARY NAMELINK_SKIP)


