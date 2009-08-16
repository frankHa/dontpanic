#ifndef DP_PERSISTANCE_BACKEND_HPP
#define DP_PERSISTANCE_BACKEND_HPP
// ---------------------------------------------------------------------------------
#include "defines.hpp"
//Qt includes
#include <QObject>
// ---------------------------------------------------------------------------------
namespace dp
{
  //forward decl
  class Action;
  class Project;
  // ---------------------------------------------------------------------------------
  /**
   * The idea for this is to abstract from the actual storage backend, in case we
   * want to switch it some time in the future. For now all calls are simply delegated
   * to the sqlite backend...
   */
  class PersistenceBackend
  {
      // ---------------------------------------------------------------------------------
    public:
      // ---------------------------------------------------------------------------------
      bool init();
      // ---------------------------------------------------------------------------------
      success persist ( Project &_project );
      // ---------------------------------------------------------------------------------
  };
  // ---------------------------------------------------------------------------------
  inline PersistenceBackend persistence()
  {
    return PersistenceBackend();
  }
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
#endif //DP_PERSISTANCE_BACKEND_HPP
