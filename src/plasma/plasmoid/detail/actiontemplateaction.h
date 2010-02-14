/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) <year>  <name of author>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef DP_PLASMA_APPLET_ACTIONTEMPLATEACTION_H
#define DP_PLASMA_APPLET_ACTIONTEMPLATEACTION_H

#include <kaction.h>
#include <libdontpanic/actiontemplate.hpp>

namespace dp {

namespace plasma {

namespace applet {

  namespace detail{
class ActionTemplateAction : public KAction
{
  Q_OBJECT
  signals:
    void triggered(ActionTemplate const& t);
  public:
  ActionTemplateAction(QObject* parent);
  ActionTemplateAction& setActionTemplate(dp::ActionTemplate const& templ);
  dp::ActionTemplate const& actionTemplate() const;
  
  private slots:
    void on_triggered();
  private:
    dp::ActionTemplate _M_template;
};
  }
}

}

}

#endif // DP_PLASMA_APPLET_ACTIONTEMPLATEACTION_H
