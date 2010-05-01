#include <libdontpanic/time.hpp>
// ---------------------------------------------------------------------------------
#include <QTime>
#include <libdontpanic/timerange.h>
namespace dp
{
  // ---------------------------------------------------------------------------------
  namespace time
  {
    // ---------------------------------------------------------------------------------
    long minutes(QTime const& time)
    {
      long result = time.hour()*60 + time.minute();
      return result;
    }
    // ---------------------------------------------------------------------------------    
    long full_days(TimeRange const& range)
    {
      if(!range.isValid()){return 0;}
      long minutes = range.duration();
      long hours = minutes/60;
      long days = hours/24;
      return days;
    }
    // ---------------------------------------------------------------------------------
    long days(TimeRange const& range)
    {
      if(!range.isValid()){return 0;}
      QDate const& from = range.from().date();
      QDate const& to = range.to().date();
      return (from.daysTo(to)+1);
    }
    // ---------------------------------------------------------------------------------
    int quarter(QDate const& d)
    {
      int month = d.month();
      if(month <= 3) return 1;
      if(month <= 6) return 2;
      if(month <= 9) return 3;
      return 4;
    }
    // ---------------------------------------------------------------------------------
  }
  // ---------------------------------------------------------------------------------
}//dp
