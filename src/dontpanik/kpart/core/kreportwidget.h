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

#ifndef DP_CORE_KREPORTWIDGET_H
#define DP_CORE_KREPORTWIDGET_H

#include <libdontpanic/defines.hpp>
#include <libdontpanic/report.h>
#include <QWidget>

namespace Ui
{
  class KReportWidget;
}

namespace dp
{
  namespace core
  {
    class KReportWidget : public QWidget
    {
      Q_OBJECT
      public:
        KReportWidget ( QWidget* parent = 0, Qt::WindowFlags f = 0 );
        ~KReportWidget();
        
      public slots:
        void setReport(Report const& r);
        void resetReport();
     
      private:
        void subscribe_to_report_manager_signals();
        
      private:
        Ui::KReportWidget *_M_ui;
    };
  }
}

#endif // DP_CORE_KREPORTWIDGET_H
