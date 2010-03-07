#include "libdontpanic/dbus.hpp"
#include "libdontpanic/dbus_support/action.hpp"
#include "libdontpanic/dbus_support/actiontemplate.hpp"
#include "libdontpanic/dbus_support/project.hpp"
#include "libdontpanic/dbus_support/report.h"
#include "libdontpanic/dbus_support/task.hpp"
#include "libdontpanic/dbus_support/timerange.h"
#include "libdontpanic/dbus_support/uuid.h"
#include "libdontpanic/dbus_support/worktimeperday.h"
//Qt includes
#include <QDebug>
#include <QDBusMetaType>
#include <QDBusConnectionInterface>
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
    return detail::service_to_register_with_dbus ( service, REGISTER );
  }
  // ---------------------------------------------------------------------------------
  detail::service_to_register_with_dbus DBus::unregister_service ( QString const& service )
  {
    return detail::service_to_register_with_dbus ( service, UNREGISTER );
  }
  // ---------------------------------------------------------------------------------
  detail::object_to_unregister_from_dbus DBus::unregister_object ( QString path )
  {
    return detail::object_to_unregister_from_dbus ( path );
  }
  // ---------------------------------------------------------------------------------
  void DBus::register_dp_custom_types()
  {
    qDBusRegisterMetaType<dp::Action>();
    qDBusRegisterMetaType<dp::ActionList>();
    qDBusRegisterMetaType<dp::ActionTemplate>();
    qDBusRegisterMetaType<dp::TemplateList>();
    qDBusRegisterMetaType<dp::Project>();
    qDBusRegisterMetaType<dp::ProjectList>();
    qDBusRegisterMetaType<dp::Report>();
    qDBusRegisterMetaType<dp::TimeRange>();
    qDBusRegisterMetaType<dp::Task>();
    qDBusRegisterMetaType<dp::TaskList>();
    qDBusRegisterMetaType<QDateTime>();
    qDBusRegisterMetaType<Uuid>();
    qDBusRegisterMetaType<dp::WorktimePerDay>();
    qDBusRegisterMetaType<dp::WorktimePerDayList>();
  }
  // ---------------------------------------------------------------------------------
  QDBusConnection DBus::session_bus()
  {
    return QDBusConnection::sessionBus();
  }
  // ---------------------------------------------------------------------------------
  QDBusConnection DBus::system_bus()
  {
#ifdef WIN32
    return QDBusConnection::sessionBus();
#endif //WIN32
    return QDBusConnection::systemBus();
  }
  // ---------------------------------------------------------------------------------
  //service_to_register_with_dbus impl:
  // ---------------------------------------------------------------------------------
  detail::service_to_register_with_dbus::service_to_register_with_dbus ( QString const& service, dbus_op op )
      : _M_service ( service )
      , _M_op ( op ) {}
  // ---------------------------------------------------------------------------------
  bool detail::service_to_register_with_dbus::at_session_bus()
  {
    QDBusConnection con = dbus().session_bus();
    if ( !con.isConnected() )
    {
      qWarning() << "not connected to session bus";
      return false;
    }
    if ( _M_op == REGISTER )
    {
      return con.registerService ( _M_service );
    }
    if ( con.interface()->isServiceRegistered ( _M_service ) )
    {
      return con.unregisterService ( _M_service );
    }
    return true;
  }
  // ---------------------------------------------------------------------------------
  bool detail::service_to_register_with_dbus::at_system_bus()
  {
    QDBusConnection con = dbus().system_bus();
    if ( !con.isConnected() )
    {
      qWarning() << "not connected to system bus";
      return false;
    }
    if ( _M_op == REGISTER )
    {
      bool result = con.registerService ( _M_service );
      if ( result == false )
      {
        qDebug() << "something went wrong when trying to register the DBUS service: " << _M_service;
        qDebug() << con.lastError();
        return false;
      }
      return true;
    }
    else
    {
      if ( con.interface()->isServiceRegistered ( _M_service ) )
      {
        return con.unregisterService ( _M_service );
      }
    }
    return true;
  }
  // ---------------------------------------------------------------------------------
  // object_to_unregister_from_dbus impl:
  // ---------------------------------------------------------------------------------
  detail::object_to_unregister_from_dbus::object_to_unregister_from_dbus ( QString path )
      : _M_path ( path ) {}
  // ---------------------------------------------------------------------------------
  void detail::object_to_unregister_from_dbus::from_session_bus()
  {
    from ( dbus().session_bus() );
  }
  // ---------------------------------------------------------------------------------
  void detail::object_to_unregister_from_dbus::from_system_bus()
  {
    from ( dbus().system_bus() );
  }
  // ---------------------------------------------------------------------------------
  void detail::object_to_unregister_from_dbus::from ( QDBusConnection con )
  {
    if ( !con.isConnected() )
    {
      return;
    }
    if ( con.objectRegisteredAt ( _M_path ) != 0 )
    {
      con.unregisterObject ( _M_path );
    }
  }
  // ---------------------------------------------------------------------------------
}//RemoteProxy
// ---------------------------------------------------------------------------------
