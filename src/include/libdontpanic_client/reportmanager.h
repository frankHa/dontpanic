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
#include <libdontpanic/reporttype.h>
#include <libdontpanic_client/detail/cache.hpp>
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
        typedef detail::cache<ReportType, NullReportType> cache_t;
        // ---------------------------------------------------------------------------------	
      signals:
        // ---------------------------------------------------------------------------------   
        void stored ( dp::ReportType );
        // ---------------------------------------------------------------------------------
        void removed ( dp::ReportType );
        // ---------------------------------------------------------------------------------
        void error(QString);
        // ---------------------------------------------------------------------------------
        void generated(Report);
        // ---------------------------------------------------------------------------------
      private slots:
        // ---------------------------------------------------------------------------------
        void on_stored ( dp::ReportType );
        // ---------------------------------------------------------------------------------
        void on_removed ( dp::ReportType );
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
        void store ( ReportType const& p );
        // ---------------------------------------------------------------------------------
        void remove ( ReportType const& p );
        // ---------------------------------------------------------------------------------
        ReportType load ( Uuid const& id );
        // ---------------------------------------------------------------------------------
        ReportTypeList allReportTypes();
        // ---------------------------------------------------------------------------------
      private:
        // ---------------------------------------------------------------------------------
        org::dontpanic::ReportManager *remote();
        // ---------------------------------------------------------------------------------
      private:
        // ---------------------------------------------------------------------------------
        org::dontpanic::ReportManager *_M_remote;
        // ---------------------------------------------------------------------------------
        cache_t _M_cache;
        // ---------------------------------------------------------------------------------
    };

  }

}

#endif // DP_CLIENT_PROJECTMANAGER_H
