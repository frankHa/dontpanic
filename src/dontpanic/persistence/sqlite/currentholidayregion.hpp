#ifndef DP_PERSISTANCE_SQLITE_CURRENT_HOLIDAY_REGION_HPP
#define DP_PERSISTANCE_SQLITE_CURRENT_HOLIDAY_REGION_HPP
// ---------------------------------------------------------------------------------
//dp includes
#include "libdontpanic/defines.hpp"
#include "libdontpanic/success.hpp"
//Forward decl
class QSqlQuery;
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  namespace _persistence
  {
    // ---------------------------------------------------------------------------------
    namespace _sqlite
    {
      // ---------------------------------------------------------------------------------
      class CurrentHolidayRegion
      {
          // ---------------------------------------------------------------------------------
        public:
          // ---------------------------------------------------------------------------------
          success create_table() const;
          // ---------------------------------------------------------------------------------
          success persist ( QString const&p ) const;
          // ---------------------------------------------------------------------------------
          success remove ( ) const;
          // ---------------------------------------------------------------------------------
          success load ( QString &p ) const;
          // ---------------------------------------------------------------------------------
          //success findAll ( QStringList &list ) const;
          // ---------------------------------------------------------------------------------
        private:
          // ---------------------------------------------------------------------------------
          bool exists ( ) const;
          // ---------------------------------------------------------------------------------
          success insert ( QString const&_p ) const;
          // ---------------------------------------------------------------------------------
          success update ( QString const& _p ) const;
          // ---------------------------------------------------------------------------------
          success assign_query_values_to_entity ( QSqlQuery &query, QString &p ) const;
          // ---------------------------------------------------------------------------------
      };//CurrentHolidayRegion
      // ---------------------------------------------------------------------------------
      inline CurrentHolidayRegion current_holiday_region()
      {
        return CurrentHolidayRegion();
      }
      // ---------------------------------------------------------------------------------
    }//_sqlite
    // ---------------------------------------------------------------------------------
  }//_persistance
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
#endif //!DP_PERSISTANCE_SQLITE_CURRENT_HOLIDAY_REGION_HPP
