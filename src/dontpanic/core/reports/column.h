#ifndef DP_REPORTS_COLUMN_H
#define DP_REPORTS_COLUMN_H
// ---------------------------------------------------------------------------------
#include <libdontpanic/defines.hpp>
#include "group.h"
#include <libdontpanic/uuid.h>
#include <libdontpanic/action.hpp>
#include <libdontpanic/reporttype.h>
#include <QVariant>
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  namespace reports
  {
    // ---------------------------------------------------------------------------------
    namespace column
    {
      class column
      {
        public:
          virtual ~column(){}
        public:
          virtual bool applies_to(ReportType const& t)=0;
          virtual QString name() const=0;
          virtual QVariant value_of(group *g)=0;
      };
      // ---------------------------------------------------------------------------------
      class date: public column
      {
        public:
          virtual bool applies_to(ReportType const& t)
          {
            return t.groupByTimeInterval() == ReportType::DAILY;
          }
          virtual QString name() const
          {
            return i18n("Date");
          }
          virtual QVariant value_of(group *g)
          {
            Action const& a = g->first();
            if(!a.isValid()) return "";
            return a.startTime().date();
          }
      };
      // ---------------------------------------------------------------------------------
      class week: public column
      {
        public:
          virtual bool applies_to(ReportType const& t)
          {
            return t.groupByTimeInterval() == ReportType::WEEKLY;
          }
          virtual QString name() const
          {
            return i18n("Week");
          }
          virtual QVariant value_of(group *g)
          {
            Action const& a = g->first();
            if(!a.isValid()) return "";
            return a.startTime().date().weekNumber();
          }
      };
      // ---------------------------------------------------------------------------------
      class month: public column
      {
        public:
          virtual bool applies_to(ReportType const& t)
          {
            return t.groupByTimeInterval() == ReportType::MONTHLY;
          }
          virtual QString name() const
          {
            return i18n("Month");
          }
          virtual QVariant value_of(group *g)
          {
            Action const& a = g->first();
            if(!a.isValid()) return "";
            return a.startTime().date().month();
          }
      };
      // ---------------------------------------------------------------------------------
      class quarter: public column
      {
        public:
          virtual bool applies_to(ReportType const& t)
          {
            return t.groupByTimeInterval() == ReportType::QUARTERLY;
          }
          virtual QString name() const
          {
            return i18n("Quarter");
          }
          virtual QVariant value_of(group *g)
          {
            Action const& a = g->first();
            if(!a.isValid()) return "";
            int month= a.startTime().date().month();
            if(month <4 ) return 1;
            if(month <7) return 2;
            if(month < 10) return 3;
            return 4;
          }
      };
      // ---------------------------------------------------------------------------------
      class year: public column
      {
        public:
          virtual bool applies_to(ReportType const& t)
          {        
            _M_report_type = t;
            int tg = t.groupByTimeInterval();
            return  (tg== ReportType::WEEKLY || tg == ReportType::MONTHLY || tg == ReportType::QUARTERLY);
          }
          virtual QString name() const
          {
            return i18n("Year");
          }
          virtual QVariant value_of(group *g)
          {
            Action const& a = g->first();
            if(!a.isValid()) return "";
            if(_M_report_type.groupByTimeInterval() != ReportType::WEEKLY)
            {
              return a.startTime().date().month();
            }
            int year;
            a.startTime().date().weekNumber(&year);
            return year;
          }
          ReportType _M_report_type;
      };
      // ---------------------------------------------------------------------------------
      class work_type: public column
      {
        public:
          virtual bool applies_to(ReportType const& t)
          {
            return t.groupByTimeInterval() == ReportType::MONTHLY;
          }
          virtual QString name() const
          {
            return i18n("Work Type");
          }
          virtual QVariant value_of(group *g)
          {
            Action const& a = g->first();
            if(!a.isValid()) return "";
            return a.startTime().date().month();
          }
      };
      // ---------------------------------------------------------------------------------
    }//column
    // ---------------------------------------------------------------------------------
  }//reports
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
#endif