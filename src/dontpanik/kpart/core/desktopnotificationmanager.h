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

#ifndef DP_CORE_DESKTOPNOTIFICATIONMANAGER_H
#define DP_CORE_DESKTOPNOTIFICATIONMANAGER_H
#include <libdontpanic/defines.hpp>
#include <QtCore/QObject>
#include <KComponentData>

// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  namespace core
  {
    // ---------------------------------------------------------------------------------
    class DesktopNotificationManager
          : public QObject
    {
        // ---------------------------------------------------------------------------------
        Q_OBJECT
        // ---------------------------------------------------------------------------------
      public:
        // ---------------------------------------------------------------------------------
        DesktopNotificationManager ( QObject* parent = 0 );
        // ---------------------------------------------------------------------------------
        void setComponentData(KComponentData const& data);
        // ---------------------------------------------------------------------------------
      public slots:
        // ---------------------------------------------------------------------------------
        void showNoJobTrackingWarning(QString const& msg);
        // ---------------------------------------------------------------------------------
      private:
        // ---------------------------------------------------------------------------------
        KComponentData _M_component;
        // ---------------------------------------------------------------------------------
    };
    // ---------------------------------------------------------------------------------
  }
  // ---------------------------------------------------------------------------------
}
// ---------------------------------------------------------------------------------
#endif // DP_CORE_DESKTOPNOTIFICATIONMANAGER_H
