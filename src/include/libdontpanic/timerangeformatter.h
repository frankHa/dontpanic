#ifndef DP_TIME_RANGE_FORMATTER_H
#define DP_TIME_RANGE_FORMATTER_H
// ---------------------------------------------------------------------------------
#include <libdontpanic/defines.hpp>
#include <libdontpanic/timerange.h>
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  class DP_EXPORT TimeRangeFormatter
  {
    public:
      QString pretty_filename_format ( TimeRange const& range );
      
      QString pretty_ui_format(TimeRange const& range);
  };
  // ---------------------------------------------------------------------------------
  inline TimeRangeFormatter time_range_formatter()
  {
    return TimeRangeFormatter();
  }
  // ---------------------------------------------------------------------------------
}
// ---------------------------------------------------------------------------------
#endif //DP_TIME_RANGE_FORMATTER_H
