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

#ifndef DP_CORE_KEDITACTIONDIALOG_H
#define DP_CORE_KEDITACTIONDIALOG_H

#include <libdontpanic/defines.hpp>
#include <libdontpanic/action.hpp>
#include <QDialog>
#include <QDate>

namespace Ui
{
  class KEditActionDialog;
}

namespace dp
{
    namespace core
    {

        class KEditActionDialog:public QDialog
        {
          Q_OBJECT
          
          public:            
                KEditActionDialog ( QWidget* parent = 0, Qt::WindowFlags f = 0 );
                ~KEditActionDialog(); 
                
          public slots:
            KEditActionDialog & setCurrentDay(QDate const& currentDate);
            KEditActionDialog & setAction(Action const& a);
          private slots:
            void init_ui();
            void setup_actions();
            void accepted();
          private:
            Ui::KEditActionDialog *_M_ui;
            QDate _M_current_date;
            Action _M_current_action;
        };

    }

}

#endif // DP_CORE_KEDITACTIONDIALOG_H
