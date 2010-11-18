#include <libdontpanic/reportdata.h>
#include <libdontpanic/durationformatter.h>
#include <QModelIndex>
#include <QDateTime>
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
    return _M_data.count();
  }
  // ---------------------------------------------------------------------------------
  QVariant ReportData::header ( int col ) const
  {
    if ( col < 0 || col >= _M_headers.count() ) return QVariant();
    return _M_headers.value ( col );
  }
  // ---------------------------------------------------------------------------------
  QVariant ReportData::data ( QModelIndex const& index ) const
  {
    return display_value ( rawData ( index ), _M_column_types.value ( index.column() ) );
  }
  // ---------------------------------------------------------------------------------
  QVariant ReportData::rawData ( QModelIndex const& index ) const
  {
    if ( index.row() >= _M_data.count() ) {return QVariant();}
    Row const& row = _M_data.value ( index.row() );
    if ( index.column() >= row.count() ) {return QVariant();}
    return row.value ( index.column() );
  }
  // ---------------------------------------------------------------------------------
  QVariant ReportData::display_value ( QVariant const& value, int t ) const
  {
    switch ( t )
    {
      case Percentage: return QString ( "%1%" ).arg ( value.toDouble(), 0, 'f', 2 );
      case Duration: return duration_formatter().format ( value.toInt() );
      case DateTime: return QDateTime::fromTime_t ( value.toUInt() ).toString(Qt::SystemLocaleShortDate);
      default: return value;
    }
  }
  // ---------------------------------------------------------------------------------
  QString ReportData::exportDataString() const
  {
    QString const& format = dataFormatString();
    QString result = dump_headers ( format );
    QStringList entries;
    foreach ( Row const row, _M_data )
    {
      entries << dump_data ( row, format );
    }
    qSort ( entries );
    foreach ( QString const& entry, entries )
    {
      result += "\n" + entry;
    }
    return result;
  }
  // ---------------------------------------------------------------------------------
  void ReportData::addHeader ( QString header, int column_type )
  {
    _M_headers << header;
    _M_column_types << column_type;
  }
  // ---------------------------------------------------------------------------------
  void ReportData::addRow ( ReportData::Row const& row )
  {
    _M_data.append ( row );
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
  ReportData::Data const& ReportData::data() const
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
    for ( int i = 1; i < col_count;++i )
    {
      format += ";%" + QString::number ( i + 1 );
    }
    return format;
  }
  // ---------------------------------------------------------------------------------
  QString ReportData::dump_headers ( QString const format ) const
  {
    QString result = format;
    foreach ( QString const& header , _M_headers )
    {
      result = result.arg ( header );
    }
    return result;
  }
  // ---------------------------------------------------------------------------------
  QString ReportData::dump_data ( Row const& row, QString const& format ) const
  {
    QString result = format;
    for ( int column = 0; column < _M_headers.count(); ++column )
    {
      result = result.arg ( display_value ( row.value ( column ), _M_column_types.value ( column ) ).toString() );
    }
    return result;
  }
  // ---------------------------------------------------------------------------------
  ReportData::TypeList &ReportData::columnTypes()
  {
    return _M_column_types;
  }
  // ---------------------------------------------------------------------------------
  ReportData::TypeList const& ReportData::columnTypes() const
  {
    return _M_column_types;
  }
  // ---------------------------------------------------------------------------------
}
// ---------------------------------------------------------------------------------

