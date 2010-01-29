#include <libdontpanic/actiontemplate.hpp>

// ---------------------------------------------------------------------------------
namespace dp
{
// ---------------------------------------------------------------------------------
///ctor:
// ---------------------------------------------------------------------------------
  ActionTemplate::ActionTemplate()
      : _M_id ( QUuid::createUuid() )
      , _M_task()
      , _M_project()
      , _M_name("")
      , _M_icon(""){}
// ---------------------------------------------------------------------------------
ActionTemplate::ActionTemplate ( QString const& name )
      : _M_id ( QUuid::createUuid() )
      , _M_task()
      , _M_project()
      , _M_name(name)
      , _M_icon(){}
  // ---------------------------------------------------------------------------------
  ActionTemplate::ActionTemplate ( QUuid const& id )
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
      QUuid ActionTemplate::id() const
  {
    return _M_id;
  }
  // ---------------------------------------------------------------------------------
  QUuid ActionTemplate::task() const
  {
    return _M_task;
  }
  // ---------------------------------------------------------------------------------
  ActionTemplate& ActionTemplate::setTask ( QUuid t )
  {
    _M_task = t;
    return *this;
  }
  // ---------------------------------------------------------------------------------
  QUuid ActionTemplate::project() const
  {
    return _M_project;
  }
  // ---------------------------------------------------------------------------------
  ActionTemplate& ActionTemplate::setProject ( QUuid p )
  {
    _M_project = p;
    return *this;
  }
  // ---------------------------------------------------------------------------------
  QUuid ActionTemplate::collaborationType() const
  {
    return _M_teamwork;
  }
  // ---------------------------------------------------------------------------------
  ActionTemplate& ActionTemplate::setCollaborationType ( QUuid ct )
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
