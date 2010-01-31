#include "reportmanager.h"
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  ReportManager::ReportManager ( QObject *parent )
      : QObject ( parent ){}
  // ---------------------------------------------------------------------------------
  Report ReportManager::generateCfReport(TimeRange const& range)
  {
    QString fakeData ="Typ;Projekt;Dauer (Tätigkeitsgruppe);Prozent (Tätigkeitsgruppe);Projektkommentar";
    fakeData += "\nDevelopment;RemoteProxy;66:35;37,1%;";
    fakeData += "\nSupport;Support;33:51;18,87%;";
    fakeData += "\nMultitasking;no project/other;58:36;32,66%;";
    fakeData += "\nDevelopment;CSL;04:47;2,66%;";
    fakeData += "\nITI;no project/other;15:36;8,7%;"; 
    
    return report().setReportType("comForte monthly report").setRange(range).setReportData(fakeData);
  }
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
