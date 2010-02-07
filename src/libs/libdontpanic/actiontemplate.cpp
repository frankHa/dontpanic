#include <libdontpanic/actiontemplate.hpp>
#include <libdontpanic/uuid.h>
// ---------------------------------------------------------------------------------
namespace dp
{
// ---------------------------------------------------------------------------------
///ctor:
// ---------------------------------------------------------------------------------
  ActionTemplate::ActionTemplate()
      : _M_id ( Uuid::generate() )
      , _M_task()
      , _M_project()
      , _M_name("")
      , _M_icon(""){}
  // ---------------------------------------------------------------------------------
  ActionTemplate::ActionTemplate ( QString const& name )
      : _M_id ( uuid().generate() )
      , _M_task()
      , _M_project()
      , _M_name(name)
      , _M_icon(){}
  // ---------------------------------------------------------------------------------
  ActionTemplate::ActionTemplate ( Uuid const& id )
      : _M_id ( id )
      , _M_task()
      , _M_project()
      , _M_name("")
      , _M_icon(""){}
  // ---------------------------------------------------------------------------------
  bool ActionTemplate::isValid() const
  {
    return !_M_id.isNull();
  }
  // ---------------------------------------------------------------------------------
  Uuid ActionTemplate::id() const
  {
    return _M_id;
  }
  // ---------------------------------------------------------------------------------
  Uuid ActionTemplate::task() const
  {
    return _M_task;
  }
  // ---------------------------------------------------------------------------------
  ActionTemplate& ActionTemplate::setTask ( Uuid t )
  {
    _M_task = t;
    return *this;
  }
  // ---------------------------------------------------------------------------------
  Uuid ActionTemplate::project() const
  {
    return _M_project;
  }
  // ---------------------------------------------------------------------------------
  ActionTemplate& ActionTemplate::setProject ( Uuid p )
  {
    _M_project = p;
    return *this;
  }
  // ---------------------------------------------------------------------------------
  Uuid ActionTemplate::collaborationType() const
  {
    return _M_teamwork;
  }
  // ---------------------------------------------------------------------------------
  ActionTemplate& ActionTemplate::setCollaborationType ( Uuid ct )
  {
    _M_teamwork = ct;
    return *this;
  }
  // ---------------------------------------------------------------------------------
  QString ActionTemplate::name() const
  {
    return _M_name;
  }
  // ---------------------------------------------------------------------------------
  ActionTemplate& ActionTemplate::setName ( QString name )
  {
    _M_name = name;
    return *this;
  }
  // ---------------------------------------------------------------------------------
  QString ActionTemplate::comment() const
  {
    return _M_comment;
  }
  // ---------------------------------------------------------------------------------
  ActionTemplate& ActionTemplate::setComment ( QString comment )
  {
    _M_comment = comment;
    return *this;
  }
  // ---------------------------------------------------------------------------------
  QString ActionTemplate::icon() const
  {
    return _M_icon;
  }
  // ---------------------------------------------------------------------------------
  ActionTemplate& ActionTemplate::setIcon ( QString icon )
  {
    _M_icon = icon;
    return *this;
  }
  
  // ---------------------------------------------------------------------------------
  bool DP_EXPORT operator == (dp::ActionTemplate const& lhs, dp::ActionTemplate const& rhs)
  {
    if(lhs.id().isNull())
    {
      return (rhs.id().isNull());
    }
    return lhs.id() == rhs.id();
  }
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
