#ifndef DP_DURATION_FORMATTER_H
#define DP_DURATION_FORMATTER_H
#include <libdontpanic/defines.hpp>
namespace dp
{
  class DurationFormatter
  {
    public:
      QString format(int duration);
  };
  inline DurationFormatter duration_formatter()
  {
    return DurationFormatter();
  }
}
#endif //DP_DURATION_FORMATTER_H
