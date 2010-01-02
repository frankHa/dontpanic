#ifndef LIBDONTPANICTASK_HPP
#define LIBDONTPANICTASK_HPP
// ---------------------------------------------------------------------------------
#include "defines.hpp"
#include <QString>
#include <QDateTime>
#include <QUuid>
// ---------------------------------------------------------------------------------
class QDBusArgument;
// ---------------------------------------------------------------------------------
namespace dp
{
// ---------------------------------------------------------------------------------
  class DP_EXPORT Task
  {
      // ---------------------------------------------------------------------------------
      friend QDBusArgument const& operator >> ( QDBusArgument const&arg, dp::Task & task );
      // ---------------------------------------------------------------------------------
    public:
      // ---------------------------------------------------------------------------------
      TYPE ( Task );
      // ---------------------------------------------------------------------------------
      ///ctor
      Task();
      // ---------------------------------------------------------------------------------
      Task ( QUuid const& id );
      // ---------------------------------------------------------------------------------
    public:
      // ---------------------------------------------------------------------------------
      QUuid const& id() const;
      // ---------------------------------------------------------------------------------
      QString const& name() const;
      // ---------------------------------------------------------------------------------
      void set_name ( QString name );
      // ---------------------------------------------------------------------------------
      bool is_solo_effort() const;
      // ---------------------------------------------------------------------------------
      void set_is_solo_effort ( bool s );
      // ---------------------------------------------------------------------------------
      bool is_chargeable() const;
      // ---------------------------------------------------------------------------------
      void set_is_chargeable ( bool c );
      // ---------------------------------------------------------------------------------
      QDateTime const& creation_date() const;
      // ---------------------------------------------------------------------------------
      void set_creation_date ( QDateTime date );
      // ---------------------------------------------------------------------------------
    private:
      // ---------------------------------------------------------------------------------
      QUuid  _M_id;
      // ---------------------------------------------------------------------------------
      QString _M_name;
      // ---------------------------------------------------------------------------------
      bool _M_solo_effort;
      // ---------------------------------------------------------------------------------
      bool _M_chargeable;
      // ---------------------------------------------------------------------------------
      QDateTime _M_creation_date;
      // ---------------------------------------------------------------------------------
      //TODO? Modification date
      // ---------------------------------------------------------------------------------
  };
  // ---------------------------------------------------------------------------------
  DECLARE_SMARTPOINTERS ( Task );
  // ---------------------------------------------------------------------------------
  class DP_EXPORT NullTask: public Task
  {
    public:

      NullTask() : Task ( QUuid() ) {}
  };
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
#endif //LIBDONTPANICTASK_HPP

