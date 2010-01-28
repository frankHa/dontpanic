#include "projectmanager.h"
#include "persistencebackend.hpp"

#include <KDebug>
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  ProjectManager::ProjectManager ( QObject *parent )
      : QObject ( parent ){}
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
    if(persistence().remove(p).was_successful())
    {
      emit removed(p);
    }
  }
  // ---------------------------------------------------------------------------------
  Project ProjectManager::load(QUuid const& id)
  {
    Project p(id);
    if(persistence().load(p).was_successful())
    {
      return p;
    }
    return NullProject();
  }
  // ---------------------------------------------------------------------------------
  ProjectList ProjectManager::findAll()
  {
    ProjectList list;
    persistence().findAll(list);
    return list;
  }
  // ---------------------------------------------------------------------------------
}//
// ---------------------------------------------------------------------------------

