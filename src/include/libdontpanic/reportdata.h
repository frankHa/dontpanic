#ifndef DP_REPORTDATA_H
#define DP_REPORTDATA_H
// ---------------------------------------------------------------------------------
#include <libdontpanic/defines.hpp>
#include <QVariant>
// ---------------------------------------------------------------------------------
class QModelIndex;
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  class DP_EXPORT ReportData
  {
      // ---------------------------------------------------------------------------------
    public:
      // ---------------------------------------------------------------------------------
      typedef QList<QVariant> Row;
      typedef QList<Row> Data;
      // ---------------------------------------------------------------------------------
    public:
      // ---------------------------------------------------------------------------------
      int columnCount() const;
      // ---------------------------------------------------------------------------------
      int rowCount() const;
      // ---------------------------------------------------------------------------------
      QVariant header ( int col ) const;
      // ---------------------------------------------------------------------------------
      QVariant data(QModelIndex const& index) const;
      // ---------------------------------------------------------------------------------
      QString exportDataString() const;
      // ---------------------------------------------------------------------------------
      void addHeader(QString header);
      // ---------------------------------------------------------------------------------
      void addRow ( Row const& row );
      // ---------------------------------------------------------------------------------
      QStringList const& headers() const;
      // ---------------------------------------------------------------------------------
      QStringList & headers();
      // ---------------------------------------------------------------------------------
      Data const& data()const;
      // ---------------------------------------------------------------------------------
      Data & data();
      // ---------------------------------------------------------------------------------
    private:
      // ---------------------------------------------------------------------------------
      QString dataFormatString() const;
      // ---------------------------------------------------------------------------------
      QString dump_headers(QString const format) const;
      // ---------------------------------------------------------------------------------
      QString dump_data(Row const& row, QString const& format) const;
      // ---------------------------------------------------------------------------------      
    private:
      // ---------------------------------------------------------------------------------
      QStringList _M_headers;
      // ---------------------------------------------------------------------------------
      Data _M_data;
      // ---------------------------------------------------------------------------------
  };
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
#endif //DP_REPORTDATA_H
