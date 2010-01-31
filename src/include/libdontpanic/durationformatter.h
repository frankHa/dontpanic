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
}
#endif //DP_DURATION_FORMATTER_H
