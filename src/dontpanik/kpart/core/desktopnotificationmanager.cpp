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

#include "desktopnotificationmanager.h"
#include <KNotification>
#include <QIcon>
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  namespace core
  {
    // ---------------------------------------------------------------------------------
    DesktopNotificationManager::DesktopNotificationManager ( QObject* parent )
        : QObject ( parent ){}
    // ---------------------------------------------------------------------------------
    void DesktopNotificationManager::setComponentName(QString const& name)
    {
      _M_component_name = name;
    }
    // ---------------------------------------------------------------------------------
    void DesktopNotificationManager::showNoJobTrackingWarning ( QString const& msg )
    {
      KNotification::event("NoJobTracking", i18n("Don't Panik Reminder"), msg, QIcon::fromTheme("dontpanik").pixmap(48), 0, KNotification::Persistent, "dontpanikpartd"/*_M_component_name*/);
    }
    // ---------------------------------------------------------------------------------
  }
  // ---------------------------------------------------------------------------------
}
// ---------------------------------------------------------------------------------
