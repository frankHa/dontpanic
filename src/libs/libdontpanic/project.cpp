#include "libdontpanic/project.hpp"
#include <libdontpanic/uuid.h>
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  ///ctor
  Project::Project()
      : _M_id ( Uuid::generate() )
      , _M_name ( "" )
      , _M_creation_date ( QDateTime::currentDateTime() )
      , _M_comment(""){}
  // ---------------------------------------------------------------------------------
   Project::Project(QString const& name)
      : _M_id ( Uuid::generate() )
      , _M_name ( name )
      , _M_creation_date ( QDateTime::currentDateTime() ) 
      , _M_comment(""){}
  // ---------------------------------------------------------------------------------
  Project::Project(Uuid const& id)
      : _M_id ( id )
      , _M_name ( "" )
      , _M_creation_date ( QDateTime::currentDateTime() )
      , _M_comment(""){}
  // ---------------------------------------------------------------------------------
  Uuid const& Project::id() const
  {
    return _M_id;
  }
  // ---------------------------------------------------------------------------------
  QString Project::name() const
  {
    return _M_name;
  }
  // ---------------------------------------------------------------------------------
  Project& Project::setName ( QString name )
  {
    _M_name = name;
    return *this;
  }
  // ---------------------------------------------------------------------------------
  QDateTime const& Project::creationDate() const
  {
    return _M_creation_date;
  }
  // ---------------------------------------------------------------------------------
  Project& Project::setCreationDate ( QDateTime date )
  {
    _M_creation_date = date;
    return *this;
  }
  // ---------------------------------------------------------------------------------
  QString const& Project::comment() const
  {
    return _M_comment;
  }
  // ---------------------------------------------------------------------------------
  Project& Project::setComment ( QString comment )
  {
    _M_comment = comment;
    return *this;
  }  
  // ---------------------------------------------------------------------------------
  bool operator == (dp::Project const& lhs, dp::Project const& rhs)
  {
    if(lhs.id().isNull())
    {
      return (rhs.id().isNull());
    }
    return lhs.id() == rhs.id();
  }
  // ---------------------------------------------------------------------------------
}
// ---------------------------------------------------------------------------------
