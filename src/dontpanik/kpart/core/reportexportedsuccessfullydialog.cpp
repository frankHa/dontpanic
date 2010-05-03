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
    ReportExportedSuccessfullyDialog::ReportExportedSuccessfullyDialog ( QFileInfo const& report_file, QWidget* parent, Qt::WFlags flags )
    :KDialog(parent, flags)
    , _M_report_file(report_file)
    {
      init();
    }
    // ---------------------------------------------------------------------------------
    void ReportExportedSuccessfullyDialog::init()
    {
      setCaption(i18n("Report Export"));
      setButtons(Ok|User1);
      setButtonText(User1, i18n("Send via Email"));
      connect(this, SIGNAL(user1Clicked()), SLOT(on_send_via_mail()));
    }
    // ---------------------------------------------------------------------------------
    void ReportExportedSuccessfullyDialog::on_send_via_mail()
    {      
//       QFileInfo report = _M_report_file;      
      this->done(User1);           
//       Mail mail;
//       mail.setSubject(report.fileName());
//       mail.addAttachement(report.absoluteFilePath());
//       MailInterface interface;
//       interface.send(mail); 
    }
    // ---------------------------------------------------------------------------------
  }
}

