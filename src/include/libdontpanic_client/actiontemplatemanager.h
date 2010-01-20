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

#ifndef DP_CLIENT_ACTION_TEMPLATE_MANAGER_H
#define DP_CLIENT_ACTION_TEMPLATE_MANAGER_H

#include <libdontpanic/dp_export.hpp>
#include <QObject>
#include <libdontpanic/actiontemplate.hpp>


class OrgDontpanicActionTemplateManagerInterface;
namespace org
{
  namespace dontpanic
  {
    typedef OrgDontpanicActionTemplateManagerInterface ActionTemplateManager;
  }
}


namespace dp
{

  namespace client
  {

    class DP_EXPORT ActionTemplateManager: public QObject
    {
        // ---------------------------------------------------------------------------------
        Q_OBJECT
        // ---------------------------------------------------------------------------------	
      signals:
	// ---------------------------------------------------------------------------------
	void stored(dp::ActionTemplate);
	// ---------------------------------------------------------------------------------
	void removed(dp::ActionTemplate);
	// ---------------------------------------------------------------------------------
	void error(QString);
	// ---------------------------------------------------------------------------------
      public:
        // ---------------------------------------------------------------------------------
        ActionTemplateManager ( QObject *parent = 0 );
        ~ActionTemplateManager ( );
        // ---------------------------------------------------------------------------------
      public:
        // ---------------------------------------------------------------------------------
        void store ( ActionTemplate const& p );
	// ---------------------------------------------------------------------------------
	void remove(ActionTemplate const& p);
        // ---------------------------------------------------------------------------------
        TemplateList allActionTemplates();
        // ---------------------------------------------------------------------------------
      private:
	// ---------------------------------------------------------------------------------
	org::dontpanic::ActionTemplateManager *remote();
	// ---------------------------------------------------------------------------------
      private:
        // ---------------------------------------------------------------------------------
        org::dontpanic::ActionTemplateManager *_M_remote;
        // ---------------------------------------------------------------------------------
    };

  }

}

#endif // DP_CLIENT_PROJECTMANAGER_H
