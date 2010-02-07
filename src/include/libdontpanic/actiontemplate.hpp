#ifndef DONTPANICLIB_ACTIONTEMPLATE_HPP
#define DONTPANICLIB_ACTIONTEMPLATE_HPP
// ---------------------------------------------------------------------------------
#include "defines.hpp"
#include <libdontpanic/uuid.h>
#include "task.hpp"
#include "project.hpp"
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  class ActionTemplate
  {
      // ---------------------------------------------------------------------------------
      friend QDBusArgument const& operator >> ( QDBusArgument const&arg, ActionTemplate & at );
      // ---------------------------------------------------------------------------------
    public:
      // ---------------------------------------------------------------------------------
      TYPE ( ActionTemplate );
      // ---------------------------------------------------------------------------------
      ///ctor:
      // ---------------------------------------------------------------------------------
      ActionTemplate();
      // ---------------------------------------------------------------------------------
      ActionTemplate(QString const& name);
      // ---------------------------------------------------------------------------------
      ActionTemplate(Uuid const& id);
      // ---------------------------------------------------------------------------------
    public:
      // ---------------------------------------------------------------------------------
      bool isValid() const;
      // ---------------------------------------------------------------------------------
      Uuid id() const;
      // ---------------------------------------------------------------------------------
      Uuid task() const;
      // ---------------------------------------------------------------------------------
      ActionTemplate& setTask ( Uuid );
      // ---------------------------------------------------------------------------------
      Uuid project() const;
      // ---------------------------------------------------------------------------------
      ActionTemplate& setProject ( Uuid );
      // ---------------------------------------------------------------------------------
      Uuid collaborationType() const;
      // ---------------------------------------------------------------------------------
      ActionTemplate& setCollaborationType ( Uuid );
      // ---------------------------------------------------------------------------------
      QString name() const;
      // ---------------------------------------------------------------------------------
      ActionTemplate& setName ( QString name );
      // ---------------------------------------------------------------------------------
      QString comment() const;
      // ---------------------------------------------------------------------------------
      ActionTemplate& setComment ( QString comment );
      // ---------------------------------------------------------------------------------
      QString icon() const;
      // ---------------------------------------------------------------------------------
      ActionTemplate& setIcon ( QString icon );
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
      QString _M_icon;
      // ---------------------------------------------------------------------------------
      //TODO shortcut
      // ---------------------------------------------------------------------------------
  };
  // ---------------------------------------------------------------------------------
  typedef QList<ActionTemplate> TemplateList;
  // ---------------------------------------------------------------------------------
  DECLARE_SMARTPOINTERS ( ActionTemplate );
  // ---------------------------------------------------------------------------------
  class DP_EXPORT NullActionTemplate: public ActionTemplate
  {
    public:
      // ---------------------------------------------------------------------------------
      NullActionTemplate() : ActionTemplate ( Uuid() ) {}
      // ---------------------------------------------------------------------------------
  };
  // ---------------------------------------------------------------------------------
  bool DP_EXPORT operator == (dp::ActionTemplate const& lhs, dp::ActionTemplate const& rhs);
  // ---------------------------------------------------------------------------------
  template<typename ostream>
  ostream & operator<<(ostream &out, dp::ActionTemplate const& t)
  {
    out<<"Template: "<<t.id().toString()<<", name: "<<t.name();
    return out;
  }
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
#endif //DONTPANICLIB_ACTIONTEMPLATE_HPP
