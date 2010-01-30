#########################################################################
# PRIVATE SECTION
#########################################################################
set(dontpanikpart_LIB_SRCS 
    context.cpp 
    kactiontemplateslist.cpp
    kactiontemplateslistmodel.cpp
    kprojectstablemodel.cpp
    kprojectstable.cpp
    kactionstableitemdelegate.cpp 
    kactionstablemodel.cpp
    kactionstable.cpp
    keditactiontemplatedialog.cpp 
    keditprojectdialog.cpp
    kedittaskdialog.cpp
    kprojectscombobox.cpp 
    kprojectsdialog.cpp
    kdayview.cpp
    kmainwidget.cpp
    kreporttypeslist.cpp
    kreporttypeslistmodel.cpp
    kreportrangedialog.cpp 
    kreportview.cpp 
    ktaskscombobox.cpp 
    ktasksdialog.cpp
    ktaskstable.cpp
    ktaskstablemodel.cpp    
    dont_panik_part_core.cpp
   )

set(dontpanikpart_LIB_UIS
    ui/kdayview.ui
    ui/keditactiontemplatedialog.ui
    ui/keditprojectdialog.ui
    ui/kedittaskdialog.ui
    ui/kprojectsdialog.ui
    ui/kreportrangedialog.ui
    ui/kreportview.ui
    ui/ktasksdialog.ui    
   )

qt4_wrap_ui(dontpanikpart_LIB_SRCS ${dontpanikpart_LIB_UIS})

kde4_add_library(dontpanikpartprivate SHARED ${dontpanikpart_LIB_SRCS})
target_link_libraries(dontpanikpartprivate ${KDE4_KDEUI_LIBS} ${KDE4_KIO_LIBS} ${KDE4_KPARTS_LIBS} dontpanic_lib dontpanic_client_lib)
install(TARGETS dontpanikpartprivate ${INSTALL_TARGETS_DEFAULT_ARGS} LIBRARY NAMELINK_SKIP)

