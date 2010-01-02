#include <libdontpanic/action.hpp>
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  Action::Action ()
      : _M_id ( QUuid::createUuid() )
      , _M_task ( new NullTask() )
      , _M_project ( new NullProject() )
      , _M_teamwork ( new NullCollaborationType() )
      , _M_name ( "" )
      , _M_comment ( "" )
      , _M_start()
      , _M_end()
      , _M_reviewed ( false )
      , _M_billed ( false ) {}
  // ---------------------------------------------------------------------------------
  Action::Action ( QUuid const& id )
      : _M_id ( id )
      , _M_task ( new NullTask() )
      , _M_project ( new NullProject() )
      , _M_teamwork ( new NullCollaborationType() )
      , _M_name ( "" )
      , _M_comment ( "" )
      , _M_start()
      , _M_end()
      , _M_reviewed ( false )
      , _M_billed ( false ) {}
  // ---------------------------------------------------------------------------------
  QUuid const& Action::id() const
  {
    return _M_id;
  }
  // ---------------------------------------------------------------------------------
  Task::ptr Action::task() const
  {
    return _M_task;
  }
  // ---------------------------------------------------------------------------------
  void Action::setTask ( Task::ptr t )
  {
    _M_task = t;
  }
  // ---------------------------------------------------------------------------------
  Project::ptr Action::project() const
  {
    return _M_project;
  }
  // ---------------------------------------------------------------------------------
  void Action::setProject ( Project::ptr p )
  {
    _M_project = p;
  }
  // ---------------------------------------------------------------------------------
  CollaborationType::ptr Action::collaborationType() const
  {
    return _M_teamwork;
  }
  // ---------------------------------------------------------------------------------
  void Action::setCollaborationType ( CollaborationType::ptr ct )
  {
    _M_teamwork = ct;
  }
  // ---------------------------------------------------------------------------------
  QString Action::name() const
  {
    return _M_name;
  }
  // ---------------------------------------------------------------------------------
  void Action::setName ( QString name )
  {
    _M_name = name;
  }
  // ---------------------------------------------------------------------------------
  QString Action::comment() const
  {
    return _M_comment;
  }
  // ---------------------------------------------------------------------------------
  void Action::setComment ( QString comment )
  {
    _M_comment = comment;
  }
  // ---------------------------------------------------------------------------------
  QDateTime Action::startTime() const
  {
    return _M_start;
  }
  // ---------------------------------------------------------------------------------
  void Action::setStartTime ( QDateTime const& start )
  {
    _M_start = start;
  }
  // ---------------------------------------------------------------------------------
  QDateTime Action::endTime() const
  {
    return _M_end;
  }
  // ---------------------------------------------------------------------------------
  void Action::setEndTime ( QDateTime const& end )
  {
    _M_end = end;
  }
  // ---------------------------------------------------------------------------------
  bool Action::reviewed() const
  {
    return _M_reviewed;
  }
  // ---------------------------------------------------------------------------------
  void Action::setReviewed ( bool r )
  {
    _M_reviewed = r;
  }
  // ---------------------------------------------------------------------------------
  bool Action::billed() const
  {
    return _M_billed;
  }
  // ---------------------------------------------------------------------------------
  void Action::setBilled ( bool b )
  {
    _M_billed = b;
  }
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
