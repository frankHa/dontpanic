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

#include "reportexportedsuccessfullydialog.h"
#include "reportexportedsuccessfullydialog.moc"
#include "mailinterface.h"

namespace dp
{
  namespace core
  {
    // ---------------------------------------------------------------------------------
    ReportExportedSuccessfullyDialog::ReportExportedSuccessfullyDialog ( QFileInfo const& report_file, QWidget* parent, Qt::WindowFlags flags )
    :QDialog(parent, flags)
    , _M_report_file(report_file)
    {
      init();
    }
    // ---------------------------------------------------------------------------------
    void ReportExportedSuccessfullyDialog::init()
    {
      setWindowTitle(i18n("Report Export"));
      connect(this, SIGNAL(user1Clicked()), SLOT(on_send_via_mail()));
    }
    // ---------------------------------------------------------------------------------
    void ReportExportedSuccessfullyDialog::on_send_via_mail()
    {      
       QFileInfo report = _M_report_file;            
      Mail mail;
      mail.setSubject(report.fileName());
      mail.addAttachement(report.absoluteFilePath());
      MailInterface interface;
      interface.send(mail); 
      this->accept();
    }
    // ---------------------------------------------------------------------------------
  }
}

