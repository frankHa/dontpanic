#include "persistencebackend.hpp"

//Qt includes
#include <QDebug>
#include <libdontpanic/action.hpp>
#include <kglobal.h>
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  K_GLOBAL_STATIC(PersistenceBackend, _instance);
  // ---------------------------------------------------------------------------------  
  PersistenceBackend & persistence()
  {
    return *_instance;
  }
  // ---------------------------------------------------------------------------------
  PersistenceBackend::PersistenceBackend ( QObject* parent )
  :QObject(parent){}
  // ---------------------------------------------------------------------------------
  bool PersistenceBackend::init(QString const& engine_name)
  {
    if(engine_name.toLower() == "sqlite")
    {
      return init(new _persistence::Sqlite(this));
    }
    return false;
  }
  // ---------------------------------------------------------------------------------
  bool PersistenceBackend::init(PersistenceEngine *engine)
  {
    _M_engine = engine;
    return _M_engine->init();
  }
  // ---------------------------------------------------------------------------------
  success PersistenceBackend::findAll(ActionList &actions, QDateTime const& from, QDateTime const& to)
  {
    return _M_engine->findAll(actions, from, to);
  }
  // ---------------------------------------------------------------------------------
  Action PersistenceBackend::lastAction()
  {
    return _M_engine->lastAction();
  }
  // ---------------------------------------------------------------------------------
  bool PersistenceBackend::hasActionsFor(QDate const& date)
  {
    return _M_engine->hasActionsFor(date);
  }
  // ---------------------------------------------------------------------------------
  success PersistenceBackend::persistCurrentHolidayRegion(QString const& region) const
  {
    return _M_engine->persistCurrentHolidayRegion(region);
  }
  // ---------------------------------------------------------------------------------
  success PersistenceBackend::removeCurrentHolidayRegion() const
  {
    return _M_engine->removeCurrentHolidayRegion();
  }
  // ---------------------------------------------------------------------------------
  success PersistenceBackend::loadCurrentHolidayRegion(QString & region) const
  {
    return _M_engine->loadCurrentHolidayRegion(region);
  }
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
#include "persistencebackend.moc"