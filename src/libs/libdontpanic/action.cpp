#include <libdontpanic/action.hpp>
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  Action::Action ()
      : _M_id ( QUuid::createUuid() )
      , _M_task ()
      , _M_project ( )
      , _M_teamwork ( )
      , _M_name ( "" )
      , _M_comment ( "" )
      , _M_start()
      , _M_end()
      , _M_reviewed ( false )
      , _M_billed ( false ) {}
  // ---------------------------------------------------------------------------------
  Action::Action ( QUuid const& id )
      : _M_id ( id )
      , _M_task ( )
      , _M_project ( )
      , _M_teamwork ( )
      , _M_name ( "" )
      , _M_comment ( "" )
      , _M_start()
      , _M_end()
      , _M_reviewed ( false )
      , _M_billed ( false ) {}
  // ---------------------------------------------------------------------------------
  bool Action::isValid()const
  {
    return !id().isNull();
  }
  // ---------------------------------------------------------------------------------
  QUuid const& Action::id() const
  {
    return _M_id;
  }
  // ---------------------------------------------------------------------------------
  QUuid Action::task() const
  {
    return _M_task;
  }
  // ---------------------------------------------------------------------------------
  void Action::setTask ( QUuid t )
  {
    _M_task = t;
  }
  // ---------------------------------------------------------------------------------
  QUuid Action::project() const
  {
    return _M_project;
  }
  // ---------------------------------------------------------------------------------
  void Action::setProject ( QUuid p )
  {
    _M_project = p;
  }
  // ---------------------------------------------------------------------------------
  QUuid Action::collaborationType() const
  {
    return _M_teamwork;
  }
  // ---------------------------------------------------------------------------------
  void Action::setCollaborationType ( QUuid ct )
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
  QTime Action::duration() const
  {
    if(startTime().isNull()){return QTime();}
    QDateTime end;
    if(endTime().isNull())
    {
      end = QDateTime::currentDateTime();
    } else
    {
      end = endTime();
    }
    QTime result(0, 0);
    return result.addSecs(startTime().secsTo(end));    
  }
  // ---------------------------------------------------------------------------------
  bool operator == (dp::Action const& lhs, dp::Action const& rhs)
  {
    if(!lhs.isValid())
    {
      return (!rhs.isValid());
    }
    return lhs.id() == rhs.id();
  }
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
