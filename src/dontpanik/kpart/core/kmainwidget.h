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

#ifndef DP_KMAINWIDGET_H
#define DP_KMAINWIDGET_H

#include <QtGui/QWidget>
#include <QtGui/QStackedWidget>
#include <QDate>
#include <kparts/statusbarextension.h>
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  namespace core
  {
    class KDayView;
    // ---------------------------------------------------------------------------------
    class KMainWidget : public QStackedWidget
    {
        // ---------------------------------------------------------------------------------
        Q_OBJECT
        // ---------------------------------------------------------------------------------
      public:
        // ---------------------------------------------------------------------------------
        KMainWidget ( QWidget *parent, KParts::StatusBarExtension * );
        // ---------------------------------------------------------------------------------
        ~KMainWidget();
        // ---------------------------------------------------------------------------------
      public slots:
        // ---------------------------------------------------------------------------------
        void show_dayview();
        // ---------------------------------------------------------------------------------
        void show_reportview();
        // ---------------------------------------------------------------------------------
        KParts::StatusBarExtension* statusBar();
        // ---------------------------------------------------------------------------------
      private:
        // ---------------------------------------------------------------------------------
        void init_widgets();
        // ---------------------------------------------------------------------------------
        KDayView * newDayView();
        // ---------------------------------------------------------------------------------
      private:
        // ---------------------------------------------------------------------------------
        KParts::StatusBarExtension *_M_status_bar;
        // ---------------------------------------------------------------------------------
    };
    // ---------------------------------------------------------------------------------
  }//core
  // ---------------------------------------------------------------------------------
}
// ---------------------------------------------------------------------------------
#endif // DP_KMAINWIDGET_H
