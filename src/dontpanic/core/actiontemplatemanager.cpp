#include "actiontemplatemanager.h"
#include "persistencebackend.hpp"

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
  void ActionTemplateManager::remove(ActionTemplate const& at)
  {
    if(persistence().remove(at).was_successful())
    {
      emit removed(at);
    }
  }
  // ---------------------------------------------------------------------------------
  TemplateList ActionTemplateManager::findAll()
  {
    TemplateList list;
    persistence().findAll(list);
    return list;
  }
  // ---------------------------------------------------------------------------------
}//
// ---------------------------------------------------------------------------------

