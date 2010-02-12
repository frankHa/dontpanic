#include "dontpanicengine.h"
 
#include <QDate>
#include <QTime>
 
#include <Plasma/DataContainer>
 
DontPanicEngine::DontPanicEngine(QObject* parent, const QVariantList& args)
    : Plasma::DataEngine(parent, args)
{
    // We ignore any arguments - data engines do not have much use for them
    Q_UNUSED(args)
 
    // This prevents applets from setting an unnecessarily high
    // update interval and using too much CPU.
    // In the case of a clock that only has second precision,
    // a third of a second should be more than enough.
    setMinimumPollingInterval(333);
}
 
bool DontPanicEngine::sourceRequestEvent(const QString &name)
{
    // We do not have any special code to execute the
    // first time a source is requested, so we just call
    // updateSourceEvent().
    return updateSourceEvent(name);
}
 
bool DontPanicEngine::updateSourceEvent(const QString &name)
{
    setData(name, I18N_NOOP("Time"), QTime::currentTime());
    setData(name, I18N_NOOP("Date"), QDate::currentDate());
    return true;
}
 
// This does the magic that allows Plasma to load
// this plugin.  The first argument must match
// the X-Plasma-EngineName in the .desktop file.
K_EXPORT_PLASMA_DATAENGINE(dontpanic, DontPanicEngine)
 
// this is needed since DontPanicEngine is a QObject
#include "dontpanicengine.moc"
