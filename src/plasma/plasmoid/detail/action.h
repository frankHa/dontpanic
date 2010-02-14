#ifndef DP_PLASMA_DETAIL_ACTION_H
#define DP_PLASMA_DETAIL_ACTION_H
#include <libdontpanic/defines.hpp>
#include <QDateTime>
namespace dp
{
  // ---------------------------------------------------------------------------------
  namespace plasma
  {
    // ---------------------------------------------------------------------------------
    namespace applet
    {
      namespace detail
      {
        struct Action
        {
          Action():active(false), project(""), task(""), start(), duration(0){}
          bool active;
          QString project;
          QString task;
          QDateTime start;
          int duration;
        };
      }
    }
  }
}

#endif //DP_PLASMA_DETAIL_ACTION_H