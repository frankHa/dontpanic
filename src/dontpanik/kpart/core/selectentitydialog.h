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

#ifndef DP_CORE_SELECTENTITYDIALOG_H
#define DP_CORE_SELECTENTITYDIALOG_H
// ---------------------------------------------------------------------------------
#include <libdontpanic/defines.hpp>
#include <libdontpanic/uuid.h>
// ---------------------------------------------------------------------------------
#include <QDialog>
// ---------------------------------------------------------------------------------
namespace Ui
{
  // ---------------------------------------------------------------------------------
  class SelectEntitiesDialog;
  // ---------------------------------------------------------------------------------
}
class QAbstractItemModel;
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  namespace core
  {
    // ---------------------------------------------------------------------------------
    class SelectEntityDialogModel;
    // ---------------------------------------------------------------------------------
    class SelectEntityDialog 
    : public QDialog
    {
      // ---------------------------------------------------------------------------------
      Q_OBJECT
      // ---------------------------------------------------------------------------------
      public:
        // ---------------------------------------------------------------------------------
        SelectEntityDialog ( SelectEntityDialogModel *model, QWidget* parent = 0, Qt::WindowFlags f = 0 );
        ~SelectEntityDialog();
        // ---------------------------------------------------------------------------------
      private:
        // ---------------------------------------------------------------------------------
        void init();
        // ---------------------------------------------------------------------------------
      public:
        // ---------------------------------------------------------------------------------
        void select(UuidList const& ids);
        // ---------------------------------------------------------------------------------
        UuidList selection() const;
        // ---------------------------------------------------------------------------------
      private slots:
        // ---------------------------------------------------------------------------------
        void on_select_all();
        // ---------------------------------------------------------------------------------
        void on_unselect_all();
        // ---------------------------------------------------------------------------------
      private:
        // ---------------------------------------------------------------------------------
        Ui::SelectEntitiesDialog *_M_ui;
        // ---------------------------------------------------------------------------------
        SelectEntityDialogModel *_M_model;
        // ---------------------------------------------------------------------------------
    };
    // ---------------------------------------------------------------------------------
  }
  // ---------------------------------------------------------------------------------
}
// ---------------------------------------------------------------------------------
#endif // DP_CORE_SELECTPROJECTSDIALOG_H
