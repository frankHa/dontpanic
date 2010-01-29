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
  Action& Action::setTask ( QUuid t )
  {
    _M_task = t;
    return *this;
  }
  // ---------------------------------------------------------------------------------
  QUuid Action::project() const
  {
    return _M_project;
  }
  // ---------------------------------------------------------------------------------
  Action& Action::setProject ( QUuid p )
  {
    _M_project = p;
    return *this;
  }
  // ---------------------------------------------------------------------------------
  QUuid Action::collaborationType() const
  {
    return _M_teamwork;
  }
  // ---------------------------------------------------------------------------------
  Action& Action::setCollaborationType ( QUuid ct )
  {
    _M_teamwork = ct;
    return *this;
  }
  // ---------------------------------------------------------------------------------
  QString Action::name() const
  {
    return _M_name;
  }
  // ---------------------------------------------------------------------------------
  Action& Action::setName ( QString name )
  {
    _M_name = name;
    return *this;
  }
  // ---------------------------------------------------------------------------------
  QString Action::comment() const
  {
    return _M_comment;
  }
  // ---------------------------------------------------------------------------------
  Action& Action::setComment ( QString comment )
  {
    _M_comment = comment;
    return *this;
  }
  // ---------------------------------------------------------------------------------
  QDateTime Action::startTime() const
  {
    return _M_start;
  }
  // ---------------------------------------------------------------------------------
  Action& Action::setStartTime ( QDateTime const& start )
  {
    _M_start = start;
    return *this;
  }
  // ---------------------------------------------------------------------------------
  QDateTime Action::endTime() const
  {
    return _M_end;
  }
  // ---------------------------------------------------------------------------------
  Action& Action::setEndTime ( QDateTime const& end )
  {
    _M_end = end;
    return *this;
  }
  // ---------------------------------------------------------------------------------
  bool Action::reviewed() const
  {
    return _M_reviewed;
  }
  // ---------------------------------------------------------------------------------
  Action& Action::setReviewed ( bool r )
  {
    _M_reviewed = r;
    return *this;
  }
  // ---------------------------------------------------------------------------------
  bool Action::billed() const
  {
    return _M_billed;
  }
  // ---------------------------------------------------------------------------------
  Action& Action::setBilled ( bool b )
  {
    _M_billed = b;
    return *this;
  }
  // ---------------------------------------------------------------------------------
  int Action::duration() const
  {
    QDateTime start = startTime();
    if(start.isNull()){return 0;}    
    QDateTime end;
    if(endTime().isNull())
    {
      end = QDateTime::currentDateTime();
    } else
    {
      end = endTime();
    }
    return (startTime().secsTo(end));    
  }
  // ---------------------------------------------------------------------------------
  bool Action::isActive() const
  {
    if(!startTime().isValid())return false;
    return endTime().isNull();
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
