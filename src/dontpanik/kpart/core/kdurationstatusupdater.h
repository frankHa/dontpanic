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

#ifndef KDURATIONSTATUSUPDATER_H
#define KDURATIONSTATUSUPDATER_H
#include <libdontpanic/defines.hpp>
#include "kdayview.h"
#include <kparts/statusbarextension.h>
#include <QObject>
#include <QTimer>
#include <QLabel>
namespace dp
{
  namespace core
  {
    class KDurationStatusUpdater: public QObject
    {
      Q_OBJECT
      public:
        KDurationStatusUpdater ( QObject* parent = 0 );
      public:
        // ---------------------------------------------------------------------------------
        void addTo(KParts::StatusBarExtension*);        
        // ---------------------------------------------------------------------------------
      public slots:
        // ---------------------------------------------------------------------------------
        void onCurrentlySelectedDaysDurationChanged ( int duration );
        // ---------------------------------------------------------------------------------
        void onCurrentProjectChanged ( QString const& project_description );
        // ---------------------------------------------------------------------------------        
        void initLabel();
        // ---------------------------------------------------------------------------------
      private:        
        // ---------------------------------------------------------------------------------
        KParts::StatusBarExtension * statusBar();
        QLabel* label();
      private:
        KParts::StatusBarExtension *_M_status_bar;
        QLabel *_M_duration_label;
    };
  }
}

#endif // KDURATIONSTATUSUPDATER_H
