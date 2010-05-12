#include <libdontpanic/timerangeformatter.h>
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  namespace detail
  {
    bool is_complete_month(TimeRange const& range)
    {
      int from_month = range.from().date().month();
      int to_month = range.to().date().month();
      if(from_month != to_month)return false;
      if(range.from().addSecs(-1).date().month() == from_month) return false;
      if(range.to().addSecs(1).date().month() == to_month) return false;
      return true;
    }
  }
  // ---------------------------------------------------------------------------------
  QString TimeRangeFormatter::pretty_filename_format ( TimeRange const& range )
  {
    if(detail::is_complete_month(range))
    {
      return range.from().toString("yyyy_MMMM");
    }
    QString result("%1_%2");
    return result.arg(range.from().date().toString(Qt::DefaultLocaleShortDate)).arg(range.to().date().toString(Qt::DefaultLocaleShortDate));        
    
  }
  // ---------------------------------------------------------------------------------
  QString TimeRangeFormatter::pretty_ui_format(TimeRange const& range)
  {
    if(detail::is_complete_month(range))
    {
      return range.from().toString("MMMM yyyy");
    }
    QString result("%1 - %2");
    return result.arg(range.from().date().toString()).arg(range.to().date().toString());        
  }
  // ---------------------------------------------------------------------------------
}
// ---------------------------------------------------------------------------------