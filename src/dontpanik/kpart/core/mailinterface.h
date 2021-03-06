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

#ifndef DP_CORE_MAILINTERFACE_H
#define DP_CORE_MAILINTERFACE_H
#include <dontpanik/defines.hpp>
//#ifdef DP_KMAIL_INTEGRATION
#include <remote_kmail.h>
#include <QObject>
// ---------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  namespace core
  {
    // ---------------------------------------------------------------------------------
    class Mail
    {
        // ---------------------------------------------------------------------------------
      public:
        // ---------------------------------------------------------------------------------
        Mail();
        // ---------------------------------------------------------------------------------
      public:
        // ---------------------------------------------------------------------------------
        void setSubject ( QString const& subject );
        // ---------------------------------------------------------------------------------
        QString subject() const;
        // ---------------------------------------------------------------------------------
        void addAttachement ( QUrl const& att );
        // ---------------------------------------------------------------------------------
        QStringList const& attachements() const;
        // ---------------------------------------------------------------------------------
      private:
        // ---------------------------------------------------------------------------------
        QString _M_subject;
        // ---------------------------------------------------------------------------------
        QStringList _M_attachement_paths;
        // ---------------------------------------------------------------------------------
    };
    // ---------------------------------------------------------------------------------
    class MailInterface
          : public QObject
    {
        // ---------------------------------------------------------------------------------
        Q_OBJECT
        // ---------------------------------------------------------------------------------
      public:
        // ---------------------------------------------------------------------------------
        MailInterface ( QObject *parent = 0 );
        // ---------------------------------------------------------------------------------
        bool isAvailable();
        // ---------------------------------------------------------------------------------
        void send ( Mail const& mail );
        // ---------------------------------------------------------------------------------
      private:
        // ---------------------------------------------------------------------------------
        org::kde::kmail::kmail *remote();
        // ---------------------------------------------------------------------------------
      private:
        // ---------------------------------------------------------------------------------
        org::kde::kmail::kmail *_M_remote;
        // ---------------------------------------------------------------------------------        
    };

  }//core
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
//#endif //DP_KMAIL_INTEGRATION
#endif // DP_CORE_MAILINTERFACE_H
