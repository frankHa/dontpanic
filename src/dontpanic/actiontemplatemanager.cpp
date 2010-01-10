#include "actiontemplatemanager.h"
#include "persistencebackend.hpp"

#include <KDebug>
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  ActionTemplateManager::ActionTemplateManager ( QObject *parent )
      : QObject ( parent ){}
  // ---------------------------------------------------------------------------------
  void ActionTemplateManager::store ( ActionTemplate const& p )
  {
    if(persistence().persist(p).was_successful())
       {
        emit stored(p);
       }
  }
  // ---------------------------------------------------------------------------------
  void ActionTemplateManager::remove(ActionTemplate const& p)
  {
    if(persistence().remove(p).was_successful())
    {
      emit removed(p);
    }
  }
  // ---------------------------------------------------------------------------------
  TemplateList ActionTemplateManager::allTemplates()
  {
    TemplateList list;
    persistence().findAll(list);
    return list;
  }
  // ---------------------------------------------------------------------------------
}//
// ---------------------------------------------------------------------------------

