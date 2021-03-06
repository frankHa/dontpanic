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

#ifndef DP_CORE_KEDITTASKDIALOG_H
#define DP_CORE_KEDITTASKDIALOG_H
#include <libdontpanic/defines.hpp>
#include <libdontpanic/task.hpp>
#include <QDialog>


namespace Ui
{
  class KEditTaskDialog;
}

namespace dp
{
  namespace core
  {
    class KEditTaskDialog : public QDialog
    {
      Q_OBJECT
      public:
        KEditTaskDialog(QWidget *parent=0);
        ~KEditTaskDialog();
      private:
        void setup_actions();
        
      public slots:
        KEditTaskDialog& setTask(Task const& t);
        
      private slots:
        void accepted();
        void rejected();
        
      private:
        Ui::KEditTaskDialog *_M_ui;
        Task _M_current_task;
    };
  }
}

#endif // DP_CORE_KEDITTASKDIALOG_H
