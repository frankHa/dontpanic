#ifndef DURATION_FORMATTER_TEST_H
#define DURATION_FORMATTER_TEST_H
// ---------------------------------------------------------------------------------
#include <QtTest/QtTest>
#include <QObject>
#include <libdontpanic/action.hpp>
// ---------------------------------------------------------------------------------
class DurationFormatterTest
      : public QObject
{
    // ---------------------------------------------------------------------------------
    Q_OBJECT
    // ---------------------------------------------------------------------------------
  private slots:
    // ---------------------------------------------------------------------------------
    void format_data();
    void format();
    // ---------------------------------------------------------------------------------
};
// ---------------------------------------------------------------------------------
#endif //DURATION_FORMATTER_TEST_H
