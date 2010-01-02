#ifndef DP_SQLITE_HPP
#define DP_SQLITE_HPP
//dp includes
#include "libdontpanic/defines.hpp"
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  //forward decl:
  FORWARD_DECL ( Action );
  class Project;
  class Task;
  // ---------------------------------------------------------------------------------
  namespace _persistence
  {
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
        success persist ( Project const&_project );
	// ---------------------------------------------------------------------------------
	success remove (Project const& _project);
        // ---------------------------------------------------------------------------------
        success persist ( Task const&_t );
        // ---------------------------------------------------------------------------------
        success persist ( Action const&_a );
        // ---------------------------------------------------------------------------------
        Action_ptr activeAction();
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
  }//_persistance
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
#endif //DP_SQLITE_HPP
