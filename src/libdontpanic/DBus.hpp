#ifndef DP_DBUS_HPP
#define DP_DBUS_HPP
//dp includes
#include "defines.hpp"
//Qt includes
#include <QDBusConnection>
#include <QDBusAbstractAdaptor>
#include <QDebug>
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  namespace detail
  {
    // ---------------------------------------------------------------------------------
    //forward decl:
    template<typename object_type>
    class object_to_register_with_dbus;
    // ---------------------------------------------------------------------------------
    class service_to_register_with_dbus;
    // ---------------------------------------------------------------------------------
  }
  // ---------------------------------------------------------------------------------
  class DP_EXPORT DBus
  {
      // ---------------------------------------------------------------------------------
    public:
      // ---------------------------------------------------------------------------------
      DBus();
      // ---------------------------------------------------------------------------------
    public:
      // ---------------------------------------------------------------------------------
      detail::service_to_register_with_dbus register_service ( QString const& service );
      // ---------------------------------------------------------------------------------
      /**
       * \brief register a dbus object with dbus
       * \example bool success = dbus().register_object(this).at_session_bus().as("/path/to/object");
       */
      template<typename object_type>
      detail::object_to_register_with_dbus<object_type>
      register_object ( object_type *object_ptr )
      {
        return detail::object_to_register_with_dbus<object_type> ( object_ptr );
      }
      // ---------------------------------------------------------------------------------
      void register_dp_custom_types();
      // ---------------------------------------------------------------------------------
  };//dbus
  // ---------------------------------------------------------------------------------
  /**
   * helper method to simplify the API:
   * this allows for code like this:
   * \example bool success = dbus().register_object(this).at_session_bus().as("/path/to/object");
   */
  inline DBus dbus()
  {
    return DBus();
  }
  // ---------------------------------------------------------------------------------
  //implementation time:
  // ---------------------------------------------------------------------------------
  template<typename object_type>
  class dbus_registration;
  // ---------------------------------------------------------------------------------



  // ---------------------------------------------------------------------------------
  /**
   * factory method to create the correct DBUS adaptor for object_type
   * we are using template specialization here to
   * let the build fail when we are trying to register an object
   * with for which don't know the correct adaptor implementation.
   * each lib/application has to provide the required specializations
   * for the adaptor types it needs to register.
   */
  template<typename object_type>
  QDBusAbstractAdaptor* create_dbus_adaptor_for ( object_type *obj );
  // ---------------------------------------------------------------------------------
  namespace detail
  {
    // ---------------------------------------------------------------------------------
    template<typename object_type>
    class dbus_registration
    {
        // ---------------------------------------------------------------------------------
      public:
        // ---------------------------------------------------------------------------------
        dbus_registration ( object_type *obj, QDBusConnection connection )
            : _M_object ( obj )
            , _M_connection ( connection ) {}
        // ---------------------------------------------------------------------------------
        bool as ( QString const& object_path )
        {
          create_dbus_adaptor_for ( _M_object );
          qDebug()<<"trying to register "<<_M_object<<" for dbus path "<<object_path;
          bool result = _M_connection.registerObject ( object_path, _M_object );
          if ( result )
          {
            qDebug() << "yeah, success :)";
          }
          else
          {
            qDebug() << "uh oh, something went wrong :(";
          }
          return result;
        }
        // ---------------------------------------------------------------------------------
      private:
        // ---------------------------------------------------------------------------------
        object_type *_M_object;
        // ---------------------------------------------------------------------------------
        QDBusConnection _M_connection;
        // ---------------------------------------------------------------------------------
    };
    // ---------------------------------------------------------------------------------
    template<typename object_type>
    class object_to_register_with_dbus
    {
        // ---------------------------------------------------------------------------------
        typedef detail::dbus_registration<object_type> dbus_registration;
        // ---------------------------------------------------------------------------------
      public:
        // ---------------------------------------------------------------------------------
        object_to_register_with_dbus ( object_type *obj )
            : _M_object ( obj ) {}
        // ---------------------------------------------------------------------------------
        dbus_registration at_system_bus()
        {
          return dbus_registration ( _M_object, QDBusConnection::systemBus() );
        }
        // ---------------------------------------------------------------------------------
        dbus_registration at_session_bus()
        {
          return dbus_registration ( _M_object, QDBusConnection::sessionBus() );
        }
        // ---------------------------------------------------------------------------------
      private:
        // ---------------------------------------------------------------------------------
        object_type * _M_object;
        // ---------------------------------------------------------------------------------
    };
    // ---------------------------------------------------------------------------------
    class DP_EXPORT service_to_register_with_dbus
    {
        // ---------------------------------------------------------------------------------
      public:
        // ---------------------------------------------------------------------------------
        service_to_register_with_dbus ( QString const& service );
        // ---------------------------------------------------------------------------------
      public:
        // ---------------------------------------------------------------------------------
        bool at_session_bus();
        // ---------------------------------------------------------------------------------
        bool at_system_bus();
        // ---------------------------------------------------------------------------------
      private:
        // ---------------------------------------------------------------------------------
        QString const& _M_service;
        // ---------------------------------------------------------------------------------
    };
    // ---------------------------------------------------------------------------------
  }//detail
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
#endif //DP_DBUS_HPP
