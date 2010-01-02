#include "projectmanager.h"
#include "persistencebackend.hpp"
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  ProjectManager::ProjectManager ( QObject *parent )
      : QObject ( parent ) {}
  // ---------------------------------------------------------------------------------
  void ProjectManager::store ( Project const& p )
  {
    if(persistence().persist(p).was_successful())
    {
      emit stored(p);
    }
  }
  // ---------------------------------------------------------------------------------
  void ProjectManager::remove(Project const& p)
  {
    emit aboutToBeRemoved(p);
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
    return list;
  }
  // ---------------------------------------------------------------------------------
}//
// ---------------------------------------------------------------------------------

