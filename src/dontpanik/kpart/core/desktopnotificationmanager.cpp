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
#include <KIcon>
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  namespace core
  {
    // ---------------------------------------------------------------------------------
    DesktopNotificationManager::DesktopNotificationManager ( QObject* parent )
        : QObject ( parent )
    {

    }
    // ---------------------------------------------------------------------------------
    void DesktopNotificationManager::showWarning ( QString const&title, QString const& msg )
    {
      KNotification::event(KNotification::Warning, title, msg, KIcon("dontpanik").pixmap(48), 0, KNotification::Persistant);
    }
    // ---------------------------------------------------------------------------------
  }
  // ---------------------------------------------------------------------------------
}
// ---------------------------------------------------------------------------------
