#########################################################################
# PRIVATE SECTION
#########################################################################
set(dontpanikpart_LIB_SRCS
    context.cpp 
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

kde4_add_library(dontpanikpartprivate SHARED ${dontpanikpart_LIB_SRCS})
target_link_libraries(dontpanikpartprivate ${KDE4_KDEUI_LIBS} dontpanic_lib dontpanic_client_lib)
install(TARGETS dontpanikpartprivate ${INSTALL_TARGETS_DEFAULT_ARGS} LIBRARY NAMELINK_SKIP)

