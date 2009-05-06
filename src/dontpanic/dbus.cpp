#include "dbus.hpp"
#include "applicationadaptor.h"
//Qt includes
#include <QDebug>
// ---------------------------------------------------------------------------------
namespace dp
{
  namespace detail
  {
    // ---------------------------------------------------------------------------------
    // implementions for the well known Adaptor types:
    // ---------------------------------------------------------------------------------
    template<>
    QDBusAbstractAdaptor* create_dbus_adaptor_for<Application> ( Application *obj )
    {
      return new ApplicationAdaptor ( obj );
    }
  }//detail
  // ---------------------------------------------------------------------------------
  //dbus impl:
  // ---------------------------------------------------------------------------------
  // static stuff:
  // ---------------------------------------------------------------------------------
  dbus *dbus::_M_instance = new dbus();
  // ---------------------------------------------------------------------------------
  dbus *dbus::self()
  {
    return _M_instance;
  }
  // ---------------------------------------------------------------------------------
  // ctor (private)
  dbus::dbus() {}
  // ---------------------------------------------------------------------------------
  detail::service_to_register_with_dbus dbus::register_service ( QString const& service )
  {
    return detail::service_to_register_with_dbus ( service );
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
