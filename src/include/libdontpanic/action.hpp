#ifndef DONTPANICLIB_ACTION_HPP
#define DONTPANICLIB_ACTION_HPP
// ---------------------------------------------------------------------------------
#include "defines.hpp"
#include <libdontpanic/timerange.h>
#include <libdontpanic/uuid.h>
//Qt includes
#include <QString>
#include <QDateTime>
#include <QMetaType>


class QDBusArgument;
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  class DP_EXPORT Action
  {
      // ---------------------------------------------------------------------------------
      friend QDBusArgument const& operator >> ( QDBusArgument const&arg, Action & action );
      // ---------------------------------------------------------------------------------
    public:
      // ---------------------------------------------------------------------------------
      TYPE ( Action );
      // ---------------------------------------------------------------------------------
      Action();
      // ---------------------------------------------------------------------------------
      Action(Uuid const& id);
      // ---------------------------------------------------------------------------------
    public:
      // ---------------------------------------------------------------------------------
      bool isValid() const;
      // ---------------------------------------------------------------------------------
      Uuid const& id() const;
      // ---------------------------------------------------------------------------------
      Uuid task() const;
      // ---------------------------------------------------------------------------------
      Action& setTask ( Uuid );
      // ---------------------------------------------------------------------------------
      Uuid project() const;
      // ---------------------------------------------------------------------------------
      Action& setProject ( Uuid );
      // ---------------------------------------------------------------------------------
      Uuid collaborationType() const;
      // ---------------------------------------------------------------------------------
      Action& setCollaborationType ( Uuid );
      // ---------------------------------------------------------------------------------
      QString name() const;
      // ---------------------------------------------------------------------------------
      Action& setName ( QString name );
      // ---------------------------------------------------------------------------------
      QString comment() const;
      // ---------------------------------------------------------------------------------
      Action& setComment ( QString comment );
      // ---------------------------------------------------------------------------------
      QDateTime startTime() const;
      // ---------------------------------------------------------------------------------
      Action& setStartTime ( QDateTime const& start );
      // ---------------------------------------------------------------------------------
      QDateTime endTime() const;
      // ---------------------------------------------------------------------------------
      Action& setEndTime ( QDateTime const& end );
      // ---------------------------------------------------------------------------------
      bool reviewed() const;
      // ---------------------------------------------------------------------------------
      Action& setReviewed ( bool r );
      // ---------------------------------------------------------------------------------
      bool billed() const;
      // ---------------------------------------------------------------------------------
      Action& setBilled ( bool b );
      // ---------------------------------------------------------------------------------
      int duration()const;
      // ---------------------------------------------------------------------------------
      bool isActive() const;
      // ---------------------------------------------------------------------------------
    private:
      // ---------------------------------------------------------------------------------
      Uuid _M_id;
      // ---------------------------------------------------------------------------------
      Uuid _M_task;
      // ---------------------------------------------------------------------------------
      Uuid _M_project;
      // ---------------------------------------------------------------------------------
      Uuid _M_teamwork;
      // ---------------------------------------------------------------------------------
      //TODO person list
      // ---------------------------------------------------------------------------------
      QString _M_name;
      // ---------------------------------------------------------------------------------
      QString _M_comment;
      // ---------------------------------------------------------------------------------
      TimeRange _M_time_range;
      // ---------------------------------------------------------------------------------
      bool _M_reviewed;
      // ---------------------------------------------------------------------------------
      bool _M_billed;
      // ---------------------------------------------------------------------------------
  };//Action
  // ---------------------------------------------------------------------------------
  class NullAction:public Action
  {
    // ---------------------------------------------------------------------------------
    public:
  // ---------------------------------------------------------------------------------
  NullAction() : Action ( Uuid() ) {}
  // ---------------------------------------------------------------------------------
  };
  // ---------------------------------------------------------------------------------
  DECLARE_SMARTPOINTERS ( Action );
  // ---------------------------------------------------------------------------------
  typedef QList<Action> ActionList;
  // ---------------------------------------------------------------------------------
  bool DP_EXPORT operator == (dp::Action const& lhs, dp::Action const& rhs);
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
#endif //DONTPANICLIB_ACTION_HPP
