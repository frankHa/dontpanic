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
  FORWARD_DECL(Action);
  class Project;
  class Task;
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
      success persist ( Project const&_project );
      // ---------------------------------------------------------------------------------
      success persist ( Task const&_t );
      // ---------------------------------------------------------------------------------
      success persist ( Action const&_a );
      // ---------------------------------------------------------------------------------
      Action_ptr activeAction();
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
