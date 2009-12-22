#include "libdontpanic/project.hpp"
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  ///ctor
  Project::Project()
      : _M_id ( QUuid::createUuid() )
      , _M_name ( "" )
      , _M_visible ( true )
      , _M_creation_date ( QDateTime::currentDateTime() ) {}
  // ---------------------------------------------------------------------------------
  Project::Project(QUuid const& id)
      : _M_id ( id )
      , _M_name ( "" )
      , _M_visible ( true )
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
  bool Project::isVisible() const
  {
    return _M_visible;
  }
  // ---------------------------------------------------------------------------------
  void Project::setIsVisible ( bool visible )
  {
    _M_visible = visible;
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
}
// ---------------------------------------------------------------------------------
