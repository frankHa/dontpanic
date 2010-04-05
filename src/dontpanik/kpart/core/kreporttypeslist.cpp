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
#include "editreporttypedialog.h"
#include "context.h"
#include <KAction>
#include <QMenu>
#include <QContextMenuEvent>
#include <KMessageBox>
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
      _M_generate_report = new KAction(i18n("Generate Report"), this );
      connect(_M_generate_report, SIGNAL(triggered()), this, SLOT(generate_report_of_selected_type()));
      _M_add_report_type = new KAction(i18n("Define a new Report Type"), this);
      connect(_M_add_report_type, SIGNAL(triggered()), this, SLOT(on_new_report_type()));
      _M_edit_selected_report_type = new KAction(i18n("Edit Report Type"), this);
      connect(_M_edit_selected_report_type, SIGNAL(triggered()), this, SLOT(on_edit_selected_report_type()));
      _M_remove_selected_report_type = new KAction(i18n("Remove Report Type"), this);
      connect(_M_remove_selected_report_type, SIGNAL(triggered()), this, SLOT(on_delete_selected_report_type()));
    }
    // ---------------------------------------------------------------------------------
    void KReportTypesList::contextMenuEvent(QContextMenuEvent *evt)
    {
      Q_UNUSED(evt);
      QMenu menu;
      if(this->selectionModel()->hasSelection())
      {
        menu.addAction(_M_generate_report);
        menu.addSeparator();
      }
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
      EditReportTypeDialog dlg;
      dlg.exec();
    }
    // ---------------------------------------------------------------------------------
    void KReportTypesList::on_delete_selected_report_type()
    {
      ReportType current_selection = _M_model->at(currentIndex());  
      if(KMessageBox::questionYesNo(this, i18n("Do you really want to remove the selected report type?"), i18n("Remove Report Type"))==KMessageBox::Yes)
      {
        kDebug()<<"attempting to delete report type"<<current_selection.id().toString();
        context()->reportManager()->remove(current_selection);
      }
    }
    // ---------------------------------------------------------------------------------
    void KReportTypesList::on_edit_selected_report_type()
    {
      ReportType current_selection = _M_model->at(currentIndex());
      EditReportTypeDialog dlg;
      dlg.setReportType(current_selection);
      dlg.exec();
    }
    // ---------------------------------------------------------------------------------
    void KReportTypesList::generate_report_of_selected_type()
    {
      on_double_clicked(currentIndex());
    }
    // ---------------------------------------------------------------------------------
    void KReportTypesList::on_double_clicked(QModelIndex const& index)
    {
      KReportRangeDialog dlg;
      if(dlg.exec()==QDialog::Accepted)
      {
        Report r =context()->reportManager()->generateReport(_M_model->at(index), dlg.selectedRange());
      }
    }
    // ---------------------------------------------------------------------------------
  }//core
  // ---------------------------------------------------------------------------------
}//dp
