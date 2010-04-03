#include "dummypersistence.hpp"
#include <libdontpanic/action.hpp>
//Qt includes
// ---------------------------------------------------------------------------------
namespace dp
{
    // ---------------------------------------------------------------------------------
    //Sqlite impl:
    // ---------------------------------------------------------------------------------
    DummyPersistence::DummyPersistence ( QObject *parent )
        : PersistenceEngine ( parent ) {}
    // ---------------------------------------------------------------------------------
    // PersistenceEngine interface:
    // ---------------------------------------------------------------------------------
    bool DummyPersistence::init()
    {
      return false;
    }
    // ---------------------------------------------------------------------------------
    success DummyPersistence::persist ( WorktimePerDay const& _wt )
    {
      return error();
    }
    // ---------------------------------------------------------------------------------
    success DummyPersistence::remove ( WorktimePerDay const& _wt )
    {
      return error();
    }
    // ---------------------------------------------------------------------------------
    success DummyPersistence::load ( WorktimePerDay & _wt ) const
    {
      return error();
    }
    // ---------------------------------------------------------------------------------
    success DummyPersistence::findAll ( WorktimePerDayList & _wl ) const
    {
      return error();
    }

    // ---------------------------------------------------------------------------------
    success DummyPersistence::persist ( Project const& _project )
    {
      projects.append(_project);
      return successful();
    }
    // ---------------------------------------------------------------------------------
    success DummyPersistence::remove ( Project const& _project )
    {
      return error();
    }
    // ---------------------------------------------------------------------------------
    success DummyPersistence::load ( Project & _project ) const
    {
      return error();
    }
    // ---------------------------------------------------------------------------------
    success DummyPersistence::findAll ( ProjectList & _pl ) const
    {
      return error();
    }
    // ---------------------------------------------------------------------------------
    success DummyPersistence::persist ( Task const& _t )
    {
      return error();
    }
    // ---------------------------------------------------------------------------------
    success DummyPersistence::load ( Task & _t ) const
    {
      return error();
    }
    // ---------------------------------------------------------------------------------
    success DummyPersistence::remove ( Task const& _t )
    {
      return error();
    }
    // ---------------------------------------------------------------------------------
    success DummyPersistence::findAll ( TaskList & _tl ) const
    {
      return error();
    }
    // ---------------------------------------------------------------------------------
    success DummyPersistence::persist ( ActionTemplate const& _t )
    {
      return error();
    }
    // ---------------------------------------------------------------------------------
    success DummyPersistence::load ( ActionTemplate & _t ) const
    {
      return error();
    }
    // ---------------------------------------------------------------------------------
    success DummyPersistence::remove ( ActionTemplate const& _t )
    {
      return error();
    }
    // ---------------------------------------------------------------------------------
    success DummyPersistence::findAll ( TemplateList & _tl ) const
    {
      return error();
    }
    // ---------------------------------------------------------------------------------
    success DummyPersistence::persist ( Action const& _a )
    {
      return error();
    }
    // ---------------------------------------------------------------------------------
    success DummyPersistence::remove ( Action const& _t )
    {
      return error();
    }
    // ---------------------------------------------------------------------------------
    success DummyPersistence::findAll ( ActionList & _tl, QDateTime const& from, QDateTime const& to ) const
    {
      return error();
    }
    // ---------------------------------------------------------------------------------
    Action DummyPersistence::lastAction() const
    {
      return NullAction();
    }
    // ---------------------------------------------------------------------------------
    bool DummyPersistence::hasActionsFor ( QDate const& date ) const
    {
      return false;
    }
    // ---------------------------------------------------------------------------------
    success DummyPersistence::persistCurrentHolidayRegion ( QString const& region )
    {
      return error();
    }
    // ---------------------------------------------------------------------------------
    success DummyPersistence::removeCurrentHolidayRegion()
    {
      return error();
    }
    // ---------------------------------------------------------------------------------
    success DummyPersistence::loadCurrentHolidayRegion ( QString & region ) const
    {
      return error();
    }
    // ---------------------------------------------------------------------------------
    success DummyPersistence::persist ( ReportType const& _t )
    {
      return error();
    }
    // ---------------------------------------------------------------------------------
    success DummyPersistence::load ( ReportType & _t ) const
    {
      return error();
    }
    // ---------------------------------------------------------------------------------
    success DummyPersistence::remove ( ReportType const& _t )
    {
      return error();
    }
    // ---------------------------------------------------------------------------------
    success DummyPersistence::findAll ( ReportTypeList & _tl ) const
    {
      return error();
    }
    // ---------------------------------------------------------------------------------  
}//dp
// ---------------------------------------------------------------------------------
#include "dummypersistence.moc"
