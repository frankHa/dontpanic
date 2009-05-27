#ifndef DP_SQLITE_HPP
#define DP_SQLITE_HPP
//dp includes
#include "defines.hpp"
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  //forward decl:
  class action;
  class project;
  // ---------------------------------------------------------------------------------
  class Sqlite
  {
      // ---------------------------------------------------------------------------------
    public:
      // ---------------------------------------------------------------------------------
      Sqlite();
      // ---------------------------------------------------------------------------------
    public:
      // ---------------------------------------------------------------------------------
      success open_database_connection();
      // ---------------------------------------------------------------------------------
      success update_database_schema_if_necessary();
      // ---------------------------------------------------------------------------------
    public:
      // ---------------------------------------------------------------------------------
      success persist ( project &_project );
      // ---------------------------------------------------------------------------------
    private:
      // ---------------------------------------------------------------------------------
      FORWARD_DECL ( sqlite_private );
      // ---------------------------------------------------------------------------------
      sqlite_private_ptr d;
      // ---------------------------------------------------------------------------------
  };
  // ---------------------------------------------------------------------------------
  inline Sqlite sqlite()
  {
    return Sqlite();
  }
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
#endif //DP_SQLITE_HPP
