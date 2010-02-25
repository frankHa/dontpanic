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

#include "actiondescription.h"
#include <libdontpanic/durationformatter.h>

namespace dp
{
  namespace plasma
  {
    namespace applet
    {
      namespace detail
      {
      QString ActionDescription::forAction(Action const& action)
      {
        if ( action.active )
        {
          QString tooltip = i18n ( "Currently working on: \nProject: %1\nTask: %2\nRunning since: %3\nCurrent duration: %4" )
          .arg ( action.project )
          .arg ( action.task )
          .arg ( action.start.time().toString ( Qt::SystemLocaleShortDate ) )
          .arg ( duration_formatter().format ( action.duration ) );
          return ( tooltip );
        }
        else
        {
          return ( i18n ( "There is currently no running activity..." ) );
        }
      }
      }
    }
  }
}

