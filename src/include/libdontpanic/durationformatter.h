#ifndef DP_DURATION_FORMATTER_H
#define DP_DURATION_FORMATTER_H
#include <libdontpanic/defines.hpp>
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  class DP_EXPORT DurationFormatter
  {
    // ---------------------------------------------------------------------------------
    public:
      // ---------------------------------------------------------------------------------
      inline QString format(int duration)
      {
        QString pattern("%L1:%L2");
        if(duration < 0)
        {
          pattern = "-" + pattern;
        }        
        int mins = duration%60;
        int h = (duration-mins)/60;
        QString result = pattern.arg(abs(h),2, 10, QChar('0')).arg(abs(mins),2, 10, QChar('0'));
        return result;
      }
      // ---------------------------------------------------------------------------------
  };
  // ---------------------------------------------------------------------------------
  inline DurationFormatter duration_formatter()
  {
    return DurationFormatter();
  }
  // ---------------------------------------------------------------------------------
}
// ---------------------------------------------------------------------------------
#endif //DP_DURATION_FORMATTER_H
