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

#ifndef DP_CORE_KTASKSDIALOG_H
#define DP_CORE_KTASKSDIALOG_H

#include <QDialog>

namespace Ui
{
  class KTasksDialog;
}

namespace dp
{

  namespace core
  {

    class KTasksDialog : public QDialog
    {
        Q_OBJECT
      public:

        KTasksDialog ( QWidget* parent = 0, Qt::WindowFlags f = 0 );
        ~KTasksDialog ( );
      
      private:
        // ---------------------------------------------------------------------------------
        void setup_actions();
        // ---------------------------------------------------------------------------------
          private slots:
        // ---------------------------------------------------------------------------------
        void add();
        // ---------------------------------------------------------------------------------
      private:
        Ui::KTasksDialog *_M_ui;
    };

  }

}

#endif // DP_CORE_KTASKSDIALOG_H
