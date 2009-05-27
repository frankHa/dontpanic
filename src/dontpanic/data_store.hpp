#ifndef DP_DATA_STORE_HPP
#define DP_DATA_STORE_HPP
// ---------------------------------------------------------------------------------
#include "defines.hpp"
// ---------------------------------------------------------------------------------
namespace dp
{
  //forward decl
  class action;
  class project;
  // ---------------------------------------------------------------------------------
  /**
   * The idea for this is to abstract from the actual storage backend, in case we
   * want to switch it some time in the future. For now all calls are simply delegated 
   * to the sqlite backend...
   */
  class DataStore
  {
      // ---------------------------------------------------------------------------------
    public:
      // ---------------------------------------------------------------------------------
      success persist(project &_project);
      // ---------------------------------------------------------------------------------
      
      // ---------------------------------------------------------------------------------
  };
  // ---------------------------------------------------------------------------------
  DataStore data_store()
  {
    return DataStore();
  }
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
#endif //DP_DATA_STORE_HPP
