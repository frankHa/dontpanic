#ifndef DP_REPORTS_CFREPORT_H
#define DP_REPORTS_CFREPORT_H
#include <libdontpanic/defines.hpp>
#include <libdontpanic/report.h>
#include <libdontpanic/timerange.h>
namespace dp
{
  namespace reports
  {
    class CFReport
    {
      public:
        CFReport &setRange(TimeRange const& );
        Report asDontPanicReport();
        
      private:
        TimeRange _M_range;
    };
    inline CFReport cfreport()
    {
      return CFReport();
    }
  }
}
#endif //DP_REPORTS_CFREPORT_H