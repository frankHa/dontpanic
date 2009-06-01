#ifndef DP_PERSISTANCE_BACKEND_HPP
#define DP_PERSISTANCE_BACKEND_HPP
// ---------------------------------------------------------------------------------
#include "defines.hpp"
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
  class PersistanceBackend
  {
      // ---------------------------------------------------------------------------------
    public:
      // ---------------------------------------------------------------------------------
      success persist(Project &_project);
      // ---------------------------------------------------------------------------------
  };
  // ---------------------------------------------------------------------------------
  PersistanceBackend persistance_backend()
  {
    return PersistanceBackend();
  }
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
#endif //DP_PERSISTANCE_BACKEND_HPP
