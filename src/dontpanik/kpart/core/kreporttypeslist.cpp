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

#include "kreporttypeslist.h"
#include "kreporttypeslistmodel.h"
#include "kreportrangedialog.h"
#include "context.h"
#include <KAction>
#include <QMenu>
#include <QContextMenuEvent>
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  namespace core
  {
    // ---------------------------------------------------------------------------------
    KReportTypesList::KReportTypesList ( QWidget *parent )
        : QListView ( parent )
        , _M_model ( new detail::KReportTypesListModel ( this ) )
    {
      setModel ( _M_model );      
      init_menu_actions();
      connect(this, SIGNAL(doubleClicked(QModelIndex const&)), SLOT(on_double_clicked(QModelIndex const&)));
    }
    // ---------------------------------------------------------------------------------
    void KReportTypesList::init_menu_actions()
    {
      _M_add_report_type = new KAction(i18n("Define a new Report Type"), this);
      connect(_M_add_report_type, SIGNAL(triggered()), this, SLOT(on_new_report_type()));
      _M_edit_selected_report_type = new KAction(i18n("Edit"), this);
      connect(_M_edit_selected_report_type, SIGNAL(triggered()), this, SLOT(on_edit_selected_report_type()));
      _M_remove_selected_report_type = new KAction(i18n("Remove"), this);
      connect(_M_remove_selected_report_type, SIGNAL(triggered()), this, SLOT(on_remove_selected_report_type()));
    }
    // ---------------------------------------------------------------------------------
    void KReportTypesList::contextMenuEvent(QContextMenuEvent *evt)
    {
      Q_UNUSED(evt);
      QMenu menu;
      menu.addAction(_M_add_report_type);
      if(this->selectionModel()->hasSelection())
      {
        menu.addSeparator();
        menu.addAction(_M_edit_selected_report_type);
        menu.addAction(_M_remove_selected_report_type);
      }
      menu.exec(evt->globalPos());      
    }
    // ---------------------------------------------------------------------------------
    void KReportTypesList::on_new_report_type()
    {
    }
    // ---------------------------------------------------------------------------------
    void KReportTypesList::on_delete_selected_report_type()
    {
    }
    // ---------------------------------------------------------------------------------
    void KReportTypesList::on_edit_selected_report_type()
    {
    }
    // ---------------------------------------------------------------------------------
    void KReportTypesList::on_double_clicked(QModelIndex const& index)
    {
      KReportRangeDialog dlg;
      if(dlg.exec()==QDialog::Accepted)
      {
        Report r =context()->reportManager()->generateReport(_M_model->at(index), dlg.selectedRange());
        //kDebug()<<r.reportData();
      }
    }
    // ---------------------------------------------------------------------------------
  }//core
  // ---------------------------------------------------------------------------------
}//dp
