#include <libdontpanic/action.hpp>
#include <libdontpanic/uuid.h>
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  Action::Action ()
      : _M_id ( uuid().generate() )
      , _M_task ()
      , _M_project ( )
      , _M_teamwork ( )
      , _M_name ( "" )
      , _M_comment ( "" )
      , _M_time_range()
      , _M_reviewed ( false )
      , _M_billed ( false ) {}
  // ---------------------------------------------------------------------------------
  Action::Action ( Uuid const& id )
      : _M_id ( id )
      , _M_task ( )
      , _M_project ( )
      , _M_teamwork ( )
      , _M_name ( "" )
      , _M_comment ( "" )
      , _M_time_range()
      , _M_reviewed ( false )
      , _M_billed ( false ) {}
  // ---------------------------------------------------------------------------------
  bool Action::isValid()const
  {
    return !id().isNull();
  }
  // ---------------------------------------------------------------------------------
  Uuid const& Action::id() const
  {
    return _M_id;
  }
  // ---------------------------------------------------------------------------------
  Uuid Action::task() const
  {
    return _M_task;
  }
  // ---------------------------------------------------------------------------------
  Action& Action::setTask ( Uuid t )
  {
    _M_task = t;
    return *this;
  }
  // ---------------------------------------------------------------------------------
  Uuid Action::project() const
  {
    return _M_project;
  }
  // ---------------------------------------------------------------------------------
  Action& Action::setProject ( Uuid p )
  {
    _M_project = p;
    return *this;
  }
  // ---------------------------------------------------------------------------------
  Uuid Action::collaborationType() const
  {
    return _M_teamwork;
  }
  // ---------------------------------------------------------------------------------
  Action& Action::setCollaborationType ( Uuid ct )
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
    return _M_time_range.from();
  }
  // ---------------------------------------------------------------------------------
  Action& Action::setStartTime ( QDateTime const& start )
  {
    _M_time_range.setFrom(start);
    return *this;
  }
  // ---------------------------------------------------------------------------------
  QDateTime Action::endTime() const
  {
    return _M_time_range.to();
  }
  // ---------------------------------------------------------------------------------
  Action& Action::setEndTime ( QDateTime const& end )
  {
    _M_time_range.setTo(end);
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
    return _M_time_range.duration();
  }
  // ---------------------------------------------------------------------------------
  bool Action::isActive() const
  {
    if(!isValid()) return false;
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
  // ActionList:
  // ---------------------------------------------------------------------------------
  int ActionList::duration()const
  {
    int result = 0;
    const_iterator iter;
    for(iter = begin();iter != end();++iter)
    {
      result += iter->duration();
    }
    return result;
  }
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
