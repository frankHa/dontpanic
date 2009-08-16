#include "DBus.hpp"
#include "libdontpanic/dbus_support/Project.hpp"
//Qt includes
#include <QDebug>
#include <QDBusMetaType>

// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  //dbus impl:
  // ---------------------------------------------------------------------------------
  // ctor
  DBus::DBus() {}
  // ---------------------------------------------------------------------------------
  detail::service_to_register_with_dbus DBus::register_service ( QString const& service )
  {
    return detail::service_to_register_with_dbus ( service );
  }
  // ---------------------------------------------------------------------------------
  void DBus::register_dp_custom_types()
  {
    qDBusRegisterMetaType<dp::Project>();
  }

  // ---------------------------------------------------------------------------------
  //service_to_register_with_dbus impl:
  // ---------------------------------------------------------------------------------
  detail::service_to_register_with_dbus::service_to_register_with_dbus ( QString const& service )
      : _M_service ( service ) {}
  // ---------------------------------------------------------------------------------
  bool detail::service_to_register_with_dbus::at_session_bus()
  {
    return QDBusConnection::sessionBus().registerService ( _M_service );
  }
  // ---------------------------------------------------------------------------------
  bool detail::service_to_register_with_dbus::at_system_bus()
  {
    bool result = QDBusConnection::systemBus().registerService ( _M_service );
    if(result == false)
    {
      qDebug()<<"something went wrong when trying to register the DBUS service: "<<_M_service;
      qDebug()<<"exiting now!!!";
      exit(-1);
    }
    return true;
  }
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
