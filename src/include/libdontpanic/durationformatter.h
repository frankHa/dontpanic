#ifndef DP_DURATION_FORMATTER_H
#define DP_DURATION_FORMATTER_H
#include <libdontpanic/defines.hpp>
namespace dp
{
  class DurationFormatter
  {
    public:
      inline QString format(int duration)
      {
        int mins = duration%60;
        int h = (duration-mins)/60;
        QString result = QString("%L1:%L2").arg(h,2, 10, QChar('0')).arg(mins,2, 10, QChar('0'));
        return result;
      }
  };
  inline DurationFormatter duration_formatter()
  {
    return DurationFormatter();
  }
}
#endif //DP_DURATION_FORMATTER_H
