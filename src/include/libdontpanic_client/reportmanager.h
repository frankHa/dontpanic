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

#ifndef DP_CLIENT_REPORTMANAGER_H
#define DP_CLIENT_REPORTMANAGER_H

#include <libdontpanic/dp_export.hpp>
#include <libdontpanic/defines.hpp>
#include <libdontpanic/report.h>
#include <QObject>


class OrgDontpanicReportManagerInterface;
namespace org
{
  namespace dontpanic
  {
    typedef OrgDontpanicReportManagerInterface ReportManager;
  }
}


namespace dp
{
  class TimeRange;
  namespace client
  {

    class DP_EXPORT ReportManager: public QObject
    {
        // ---------------------------------------------------------------------------------
        Q_OBJECT
        // ---------------------------------------------------------------------------------	
      signals:
        // ---------------------------------------------------------------------------------    
        void error(QString);
        void generated(Report);
        // ---------------------------------------------------------------------------------
      private slots:
        // ---------------------------------------------------------------------------------
      public:
        // ---------------------------------------------------------------------------------
        ReportManager ( QObject *parent = 0 );
        ~ReportManager ( );
        // ---------------------------------------------------------------------------------
      public:
        // ---------------------------------------------------------------------------------
        Report generateCfReport(TimeRange const& range);
        // ---------------------------------------------------------------------------------
      private:
        // ---------------------------------------------------------------------------------
        org::dontpanic::ReportManager *remote();
        // ---------------------------------------------------------------------------------
      private:
        // ---------------------------------------------------------------------------------
        org::dontpanic::ReportManager *_M_remote;
        // ---------------------------------------------------------------------------------
    };

  }

}

#endif // DP_CLIENT_PROJECTMANAGER_H
