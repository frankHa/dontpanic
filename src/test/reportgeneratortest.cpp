#include "reportgeneratortest.h"
#include "dummypersistence.hpp"
#include <libdontpanic/project.hpp>
// ---------------------------------------------------------------------------------
dp::DummyPersistence persistence;
// ---------------------------------------------------------------------------------
void ReportGeneratorTest::initTestCase()
{
  dp::Project p1;
  p1.setName("Project 1");
  dp::Project p2;
  p2.setName("Project 2");
  persistence.projects<<p1<<p2;
  
  dp::Task t1;
  t1.setName("Task 1");
  dp::Task t2;
  t2.setName("Task 2");
  persistence.tasks<<t1<<t2;
  
}
// ---------------------------------------------------------------------------------
void ReportGeneratorTest::init()
{
}
// ---------------------------------------------------------------------------------
void ReportGeneratorTest::cleanup()
{
}
// ---------------------------------------------------------------------------------
QTEST_MAIN ( ReportGeneratorTest )
#include "reportgeneratortest.moc"
