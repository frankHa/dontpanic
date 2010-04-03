#ifndef DP_PERSISTANCE_BACKEND_HPP
#define DP_PERSISTANCE_BACKEND_HPP
// ---------------------------------------------------------------------------------
#include "libdontpanic/defines.hpp"
#include "persistence/sqlite.hpp"

//Qt includes
#include <QObject>
// ---------------------------------------------------------------------------------
namespace dp
{
  //forward decl
  FORWARD_DECL ( Action );
  // ---------------------------------------------------------------------------------
  /**
   * The idea for this is to abstract from the actual storage backend, in case we
   * want to switch it some time in the future. For now all calls are simply delegated
   * to the sqlite backend...
   */
  class PersistenceBackend
        : public QObject
  {
      // ---------------------------------------------------------------------------------
      Q_OBJECT
      // ---------------------------------------------------------------------------------
    public:
      // ---------------------------------------------------------------------------------
      PersistenceBackend ( QObject* parent = 0 );
      // ---------------------------------------------------------------------------------
    public:
      // ---------------------------------------------------------------------------------
      bool init ( QString const& engine_name );
      // ---------------------------------------------------------------------------------
      bool init ( PersistenceEngine *engine );
      // ---------------------------------------------------------------------------------
      template<typename T>
      success persist ( T const&_t )
      {
        return _M_engine->persist ( _t );
      }
      // ---------------------------------------------------------------------------------
      template<typename T>
      success remove ( T const& _t )
      {
        return _M_engine->remove ( _t );
      }
      // ---------------------------------------------------------------------------------
      template<typename T>
      success load ( T & _t )
      {
        return _M_engine->load ( _t );
      }
      // ---------------------------------------------------------------------------------
      template<typename ListT>
      success findAll ( ListT & _l )
      {
        return _M_engine->findAll ( _l );
      }
      // ---------------------------------------------------------------------------------
      success findAll ( ActionList &actions, QDateTime const& from, QDateTime const& to );
      // ---------------------------------------------------------------------------------
      Action lastAction();
      // ---------------------------------------------------------------------------------
      bool hasActionsFor ( QDate const& date );
      // ---------------------------------------------------------------------------------
      success persistCurrentHolidayRegion ( QString const& region ) const;
      // ---------------------------------------------------------------------------------
      success removeCurrentHolidayRegion() const;
      // ---------------------------------------------------------------------------------
      success loadCurrentHolidayRegion ( QString & region ) const;
      // ---------------------------------------------------------------------------------
    private:
      // ---------------------------------------------------------------------------------
      PersistenceEngine *_M_engine;
      // ---------------------------------------------------------------------------------
  };
  // ---------------------------------------------------------------------------------
  PersistenceBackend & persistence();
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
#endif //DP_PERSISTANCE_BACKEND_HPP
