#include "libdontpanic/project.hpp"
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  ///ctor
  Project::Project()
      : _M_id ( QUuid::createUuid() )
      , _M_name ( "" )
      , _M_creation_date ( QDateTime::currentDateTime() ) {}
  // ---------------------------------------------------------------------------------
   Project::Project(QString const& name)
      : _M_id ( QUuid::createUuid() )
      , _M_name ( name )
      , _M_creation_date ( QDateTime::currentDateTime() ) {}
  // ---------------------------------------------------------------------------------
  Project::Project(QUuid const& id)
      : _M_id ( id )
      , _M_name ( "" )
      , _M_creation_date ( QDateTime::currentDateTime() ) {}
  // ---------------------------------------------------------------------------------
  QUuid const& Project::id() const
  {
    return _M_id;
  }
  // ---------------------------------------------------------------------------------
  QString Project::name() const
  {
    return _M_name;
  }
  // ---------------------------------------------------------------------------------
  void Project::setName ( QString name )
  {
    _M_name = name;
  }
  // ---------------------------------------------------------------------------------
  QDateTime const& Project::creationDate() const
  {
    return _M_creation_date;
  }
  // ---------------------------------------------------------------------------------
  void Project::setCreationDate ( QDateTime date )
  {
    _M_creation_date = date;
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
