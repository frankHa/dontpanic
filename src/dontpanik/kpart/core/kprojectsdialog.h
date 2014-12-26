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

#ifndef KPROJECTSDIALOG_H
#define KPROJECTSDIALOG_H

#include <QDialog>
// ---------------------------------------------------------------------------------
namespace Ui
{
  class KProjectsDialog;
}
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  namespace core
  {
    // ---------------------------------------------------------------------------------
    class KProjectsDialog
          : public QDialog
    {
        // ---------------------------------------------------------------------------------
        Q_OBJECT
        // ---------------------------------------------------------------------------------
      public:
        // ---------------------------------------------------------------------------------
        KProjectsDialog ( QWidget *parent );
        // ---------------------------------------------------------------------------------
        ~KProjectsDialog ();
        // ---------------------------------------------------------------------------------
      private:
        // ---------------------------------------------------------------------------------
        void setup_actions();
        // ---------------------------------------------------------------------------------
      private slots:
        // ---------------------------------------------------------------------------------
        void add();
        // ---------------------------------------------------------------------------------
      private:
        // ---------------------------------------------------------------------------------
        Ui::KProjectsDialog *_M_ui;
        // ---------------------------------------------------------------------------------
    };
    // ---------------------------------------------------------------------------------
  }//core
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
#endif // KPROJECTSDIALOG_H
