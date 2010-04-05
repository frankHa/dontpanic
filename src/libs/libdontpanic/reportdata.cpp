#include <libdontpanic/reportdata.h>
#include <QModelIndex>
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  int ReportData::columnCount() const
  {
    return _M_headers.count();
  }
  // ---------------------------------------------------------------------------------
  int ReportData::rowCount() const
  {
    _M_data.count();
  }
  // ---------------------------------------------------------------------------------
  QVariant ReportData::header ( int col ) const
  {
    if(col < 0 || col>=_M_headers.count()) return QVariant();
    return _M_headers.value(col);
  }
  // ---------------------------------------------------------------------------------
  QVariant ReportData::data(QModelIndex const& index) const
  {
    if(index.row()>=_M_data.count()){return QVariant();}
    Row const& row = _M_data.value(index.row());
    if(index.column()>=row.count()){return QVariant();}
    return row.value(index.column());
  }
  // ---------------------------------------------------------------------------------
  QString ReportData::exportDataString() const
  {
    QString const& format = dataFormatString();
    QString result = dump_headers(format);
    foreach(Row const row, _M_data)
    {
      result += "\n" + dump_data(row, format);
    }
    return result;
  }
  // ---------------------------------------------------------------------------------
  void ReportData::addHeader(QString header)
  {
    _M_headers<<header;
  }
  // ---------------------------------------------------------------------------------
  void ReportData::addRow ( ReportData::Row const& row )
  {
    _M_data.append(row);
  }
  // ---------------------------------------------------------------------------------
  QStringList const& ReportData::headers() const
  {
    return _M_headers;
  }
  // ---------------------------------------------------------------------------------
  QStringList & ReportData::headers()
  {
    return _M_headers;
  }
  // ---------------------------------------------------------------------------------
  ReportData::Data const& ReportData::data()const
  {
    return _M_data;
  }
  // ---------------------------------------------------------------------------------
  ReportData::Data & ReportData::data()
  {
    return _M_data;
  }
  // ---------------------------------------------------------------------------------
  // private stuff:
  // ---------------------------------------------------------------------------------
  QString ReportData::dataFormatString() const
  {
    int col_count = _M_headers.count();
    QString format = "%1";
    for(int i=1; i<col_count;++i)
    {
      format +=";%" + QString::number(i+1);
    }
    return format;
  }
  // ---------------------------------------------------------------------------------
  QString ReportData::dump_headers(QString const format) const
  {
    QString result = format;
    foreach(QString const& header , _M_headers)
    {
      result = result.arg(header);
    }
    return result;
  }
  // ---------------------------------------------------------------------------------
  QString ReportData::dump_data(Row const& row, QString const& format) const
  {
    QString result = format;
    foreach(QVariant const& value, row)
    {
      result = result.arg(value.toString());
    }
    return result;
  }
  // ---------------------------------------------------------------------------------
}
// ---------------------------------------------------------------------------------

