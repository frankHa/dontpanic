#include "projectmanager.h"
#include "persistencebackend.hpp"
#include <KDebug>
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  ProjectManager::ProjectManager ( QObject *parent )
      : QObject ( parent ) {}
  // ---------------------------------------------------------------------------------
  void ProjectManager::store ( Project const& p )
  {
    qWarning()<<__FUNCTION__<< p;
    if(persistence().persist(p).was_successful())
    {
      qWarning()<<__FUNCTION__<<": emitting stored("<<p<<")";
      emit stored(p);
    }
  }
  // ---------------------------------------------------------------------------------
  void ProjectManager::remove(Project const& p)
  {
    if(persistence().remove(p).was_successful())
    {
      emit removed(p);
    }
  }
  // ---------------------------------------------------------------------------------
  ProjectList ProjectManager::allProjects()
  {
    qDebug()<<__FUNCTION__;
    ProjectList list;
    persistence().findAll(list);
    return list;
  }
  // ---------------------------------------------------------------------------------
}//
// ---------------------------------------------------------------------------------

