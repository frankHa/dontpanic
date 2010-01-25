#ifndef DP_PERSISTANCE_BACKEND_HPP
#define DP_PERSISTANCE_BACKEND_HPP
// ---------------------------------------------------------------------------------
#include "libdontpanic/defines.hpp"
#include "persistence/sqlite.hpp"

//Qt includes
#include <QObject>
// ---------------------------------------------------------------------------------
namespace dp
{
  //forward decl
  FORWARD_DECL(Action);
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
      template<typename T>
      success persist ( T const&_t )
      {
        return _persistence::sqlite().persist ( _t );
      }
      // ---------------------------------------------------------------------------------
      template<typename T>
      success remove (T const& _t)
      {
        return _persistence::sqlite().remove(_t);
      }
      // ---------------------------------------------------------------------------------
      template<typename ListT>
      success findAll(ListT & _l)
      {
        return _persistence::sqlite().findAll(_l);
      }
      // ---------------------------------------------------------------------------------
      Action activeAction();
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
