include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(dontpanic_SRCS
    Application.cpp
    main.cpp
   )

qt4_generate_dbus_interface(Application.hpp org.dontpanic.Application.xml)
qt4_add_dbus_adaptor(dontpanic_SRCS ${CMAKE_CURRENT_BINARY_DIR}/org.dontpanic.Application.xml Application.hpp Application)

kde4_add_executable(dontpanic ${dontpanic_SRCS})
target_link_libraries(dontpanic ${QT_QTCORE_LIBRARY} ${QT_QTDBUS_LIBRARY})
install(TARGETS dontpanic ${INSTALL_TARGETS_DEFAULT_ARGS} )
#install( FILES ${CMAKE_CURRENT_BINARY_DIR}/org.dontpanic.Application.xml DESTINATION ${KDE4_DBUS_INTERFACES_DIR} )