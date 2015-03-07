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
#include "mailinterface.h"
#include "reportexportedsuccessfullydialog.h"
#include <libdontpanic/report.h>
#include <QSortFilterProxyModel>
#include <QAction>
#include <QContextMenuEvent>
#include <QMenu>
#include <QFile>
#include <QDir>
#include <KMessageBox>
#include <QFileDialog>
#include <QPushButton>
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  namespace core
  {
    // ---------------------------------------------------------------------------------
    namespace detail
    {
      QUrl url ( QString const& filename )
      {
        QFileInfo fi ( filename );
        QDir const& parent = fi.absoluteDir();
        if ( parent.exists() )
        {
          return QUrl::fromLocalFile ( filename );
        }
        return QUrl::fromLocalFile ( fi.fileName() );
      }
    }
    // ---------------------------------------------------------------------------------
    KReportTable::KReportTable ( QWidget* parent )
        : QTableView ( parent )
    {
      init();
    }
    // ---------------------------------------------------------------------------------
    void KReportTable::setReport ( Report const& data )
    {
      _M_data_model->setReport ( data );
      this->resizeColumnsToContents();
    }
    // ---------------------------------------------------------------------------------
    void KReportTable::resetReport ()
    {
      _M_data_model->resetReport();
    }
    // ---------------------------------------------------------------------------------
    void KReportTable::contextMenuEvent ( QContextMenuEvent* evt )
    {
      QMenu menu;
      menu.addAction ( _M_export_data_action );
      menu.exec ( evt->globalPos() );
    }
    // ---------------------------------------------------------------------------------
    // private stuff:
    // ---------------------------------------------------------------------------------
    void KReportTable::init()
    {
      _M_data_model = new KReportTableModel ( this );
      _M_sort_model = new QSortFilterProxyModel ( this );
      _M_sort_model->setSortRole(KReportTableModel::SortRole);
      _M_sort_model->setSourceModel ( _M_data_model );
      this->setModel ( _M_sort_model );
      setup_actions();
    }
    // ---------------------------------------------------------------------------------
    void KReportTable::setup_actions()
    {
      _M_export_data_action = new QAction ( i18n ( "Export Report Data to File" ), this );
      connect ( _M_export_data_action, SIGNAL ( triggered() ), this, SLOT ( export_data_to_file() ) );
    }
    // ---------------------------------------------------------------------------------
    void KReportTable::export_data_to_file()
    {
      Uuid const&id = _M_data_model->report().reportType().id();
      //fetching the target file name from the most recent representation of the report type (instead of using the cached report type definition):
      QString filename = context()->reportManager()->load ( id ).exportDataFileName ( _M_data_model->report() );

      filename = QFileDialog::getSaveFileName ( this, i18n ( "Export Report Data to" ), detail::url ( filename ).toLocalFile());
      if ( filename.isEmpty() ) {return;}
      QFile out ( filename );
      QFileInfo out_info ( out );
      if ( out_info.exists() )
      {
        if ( KMessageBox::questionYesNo ( 0, i18n ( "The target file <b>'%1'</b> already exists. Do you really want to overwrite it?" ).arg ( filename ), i18n ( "File already exists - Don't Panik" ) ) == KMessageBox::No )
        {
          return;
        }
      }
      if ( !out.open ( QIODevice::WriteOnly ) )
      {
        KMessageBox::error ( 0, i18n ( "Unable to export Report Data to file <b>'%1'</b>.", filename ), i18n ( "Report Export Error" ) );
        return;
      }
      out.write ( _M_data_model->report().reportData().exportDataString().toLatin1() );
      out.close();
      _M_report_file = out_info;
      QDialog *dlg = new QDialog();
      dlg->setWindowTitle(i18n("Report Export"));
      QDialogButtonBox *buttons = new QDialogButtonBox(dlg);
      buttons->addButton(QDialogButtonBox::Ok);
#ifdef DP_KMAIL_INTEGRATION
      QPushButton *send_via_mail = new QPushButton(i18n("Send via Email"));
      connect(send_via_mail, SIGNAL(clicked(bool)), this, SLOT(on_send_via_mail()));
      buttons->addButton(send_via_mail, QDialogButtonBox::AcceptRole);
#endif //DP_KMAIL_INTEGRATION
      KMessageBox::createKMessageBox(dlg,
        buttons,
        QMessageBox::Information,
        i18n ( "Report exported successfully to <b>'%1'</b>." , filename ),
                                     QStringList(),QString(),0,KMessageBox::Notify);      
    }
    // ---------------------------------------------------------------------------------    
#ifdef DP_KMAIL_INTEGRATION
    void KReportTable::on_send_via_mail()    
    {      
       QFileInfo report = _M_report_file;            
      Mail mail;
      mail.setSubject(report.fileName());
      mail.addAttachement(report.absoluteFilePath());
      MailInterface interface;
      interface.send(mail); 
      //this->accept();
    }
    // ---------------------------------------------------------------------------------
#endif //DP_KMAIL_INTEGRATION
  }
  // ---------------------------------------------------------------------------------
}
// ---------------------------------------------------------------------------------

