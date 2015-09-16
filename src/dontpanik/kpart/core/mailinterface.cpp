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

#include "mailinterface.h"
//#ifdef DP_KMAIL_INTEGRATION
#include <QProcess>

namespace dp
{
  namespace core
  {
    // ---------------------------------------------------------------------------------
    Mail::Mail() : _M_subject ( "" ) {}
    // ---------------------------------------------------------------------------------
    void Mail::setSubject ( QString const& subject )
    {
      _M_subject = subject;
    }
    // ---------------------------------------------------------------------------------
    QString Mail::subject() const
    {
      return _M_subject;
    }
    // ---------------------------------------------------------------------------------
    void Mail::addAttachement ( QString const& att )
    {
      _M_attachement_paths << att;
    }
    // ---------------------------------------------------------------------------------
    QStringList const& Mail::attachements() const
    {
      return _M_attachement_paths;
    }
    // ---------------------------------------------------------------------------------
    // Mail interface:
    // ---------------------------------------------------------------------------------
    MailInterface::MailInterface ( QObject* parent )
      : QObject ( parent )
      , _M_remote ( 0 ) {}
    // ---------------------------------------------------------------------------------
    bool MailInterface::isAvailable()
    {
      bool binary_available = QProcess::execute("/bin/sh -c \"command -v kmail\"")==0;
      return binary_available or remote()->isValid();
    }
    // ---------------------------------------------------------------------------------
    void MailInterface::send ( Mail const& mail )
    {
      if ( remote()->isValid() )
      {
        QString to ( "" );
        QString cc ( "" );
        QString bcc ( "" );
        QString const& subject = mail.subject();
        QString body ( "" );
        bool hidden ( false );
        QString messageFile ( "" );
        QStringList const& attachements = mail.attachements();
        QStringList customHeaders;
        remote()->openComposer ( to, cc, bcc, subject, body, hidden, messageFile, attachements, customHeaders );
      }
      else
      {
        QStringList arguments;
        arguments << "-s" << mail.subject();
        foreach ( QString const & url, mail.attachements() )
        {
          arguments << "--attach" << url;
        }
        arguments << "--composer";
        QProcess::execute ( "kmail", arguments );
      }
    }
    // ---------------------------------------------------------------------------------
    org::kde::kmail::kmail *MailInterface::remote()
    {
      if ( _M_remote == 0 )
      {
        _M_remote = new org::kde::kmail::kmail
        ( "org.kde.kmail", "/KMail", QDBusConnection::sessionBus(), this );
        if ( !_M_remote->isValid() )
        {
          qWarning() << _M_remote->lastError();
        }
      }
      return _M_remote;
    }
    // ---------------------------------------------------------------------------------
  }
}
//#endif //DP_KMAIL_INTEGRATION
