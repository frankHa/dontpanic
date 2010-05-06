#include "durationformattertest.h"
#include <libdontpanic/durationformatter.h>
// ---------------------------------------------------------------------------------
void DurationFormatterTest::format_data()
{
  QTest::addColumn<int>("duration");
  QTest::addColumn<QString>("result");
  
  QTest::newRow("0")<<0<<"00:00";
  QTest::newRow("5")<<5<<"00:05";
  QTest::newRow("-5")<<-5<<"-00:05";
  QTest::newRow("60")<<60<<"01:00";
  QTest::newRow("-60")<<-60<<"-01:00";
}
// ---------------------------------------------------------------------------------
void DurationFormatterTest::format()
{
  QFETCH(int, duration);
  QFETCH(QString, result);
  
  QCOMPARE(dp::duration_formatter().format(duration), result);
}
// ---------------------------------------------------------------------------------
QTEST_MAIN ( DurationFormatterTest )
#include "durationformattertest.moc"
