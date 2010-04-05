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

#include "kreporttable.h"
#include "kreporttablemodel.h"
#include "context.h"
#include <libdontpanic/report.h>
#include <QSortFilterProxyModel>
#include <KAction>
#include <QContextMenuEvent>
#include <QMenu>
#include <QFile>
#include <QDir>
#include <KMessageBox>
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  namespace core
  {
    // ---------------------------------------------------------------------------------
    KReportTable::KReportTable ( QWidget* parent ) 
    : QTableView ( parent )
    {
      init();
    }
    // ---------------------------------------------------------------------------------
    void KReportTable::setReport ( Report const& data )
    {
      _M_data_model->setReport(data);
      this->resizeColumnsToContents();
    }
    // ---------------------------------------------------------------------------------
    void KReportTable::resetReport ()
    {
      _M_data_model->resetReport();
    }
    // ---------------------------------------------------------------------------------
    void KReportTable::contextMenuEvent(QContextMenuEvent* evt)
    {
      QMenu menu;
      menu.addAction(_M_export_data_action);
      menu.exec(evt->globalPos());      
    }
    // ---------------------------------------------------------------------------------
    // private stuff:
    // ---------------------------------------------------------------------------------
    void KReportTable::init()
    {
      _M_data_model = new KReportTableModel(this);
      _M_sort_model = new QSortFilterProxyModel(this);
      _M_sort_model->setSourceModel(_M_data_model);
      this->setModel(_M_sort_model);
      setup_actions();
    }
    // ---------------------------------------------------------------------------------
    void KReportTable::setup_actions()
    {
      _M_export_data_action = new KAction(i18n("Export Report Data to File"), this);
      connect(_M_export_data_action, SIGNAL(triggered()), this, SLOT(export_data_to_file()));
    }
    // ---------------------------------------------------------------------------------
    void KReportTable::export_data_to_file()
    {
      Uuid const&id = _M_data_model->report().reportType().id();
      //fetching the target file name from the most recent representation of the report type (instead of using the cached report type definition):
      QString const& filename = context()->reportManager()->load(id).exportDataFileName(_M_data_model->report());
      if(filename.isEmpty())
      {
        KMessageBox::error(0, i18n("No target file specified. Please correct the target file name in the Report definition."), i18n("Report Export Error - Don't Panik"));
        return;
      }
      QFile out(filename);
      QFileInfo out_info(out);
      if(out_info.exists())       
      {
        if(out_info.isDir())
        {
          KMessageBox::error(0, i18n("The target file <b>'%1'</b> is pointing to a directory instead of a file.<br>Please correct the target file name in the Report definition.").arg(filename), i18n("Report Export Error - Don't Panik"));
          return;
        }
        else
        {
          if(KMessageBox::questionYesNo(0, i18n("The target file <b>'%1'</b> already exists. Do you really want to overwrite it?").arg(filename), i18n("File already exists - Don't Panik")) == KMessageBox::No)
          {
            return;
          }
        }
      }
      QDir parentDir = out_info.absoluteDir();
      if(!parentDir.exists())
      {
        parentDir.mkpath(parentDir.absolutePath());
      }
      if(!out.open(QIODevice::WriteOnly))
      {
        KMessageBox::error(0, i18n("Unable to export Report Data to file <b>'%1'</b>.<br>Please correct the target file name in the Report definition and regenerate this report with the new settings.").arg(filename), i18n("Report Export Error - Don't Panik"));
        return;
      }
      out.write(_M_data_model->report().reportData().exportDataString().toAscii());
      out.close();
      KMessageBox::information(0, i18n("Report exported successfully to <b>'%1'</b>.").arg(filename), i18n("Report Export - Don't Panik"));
    }
    // ---------------------------------------------------------------------------------
  }
  // ---------------------------------------------------------------------------------
}
// ---------------------------------------------------------------------------------

