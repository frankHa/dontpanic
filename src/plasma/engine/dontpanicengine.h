// a standard include guard to prevent problems if the
// header is included multiple times
#ifndef DONTPANICENGINE_H
#define DONTPANICENGINE_H
 
// We need the DataEngine header, since we are inheriting it
#include <Plasma/DataEngine>
 
/**
 * This engine provides the current date and time for a given
 * timezone.
 *
 * "Local" is a special source that is an alias for the current
 * timezone.
 */
class DontPanicEngine : public Plasma::DataEngine
{
    // required since Plasma::DataEngine inherits QObject
    Q_OBJECT
 
    public:
        // every engine needs a constructor with these arguments
        DontPanicEngine(QObject* parent, const QVariantList& args);
 
    protected:
        // this virtual function is called when a new source is requested
        bool sourceRequestEvent(const QString& name);
 
        // this virtual function is called when an automatic update
        // is triggered for an existing source (ie: when a valid update
        // interval is set when requesting a source)
        bool updateSourceEvent(const QString& source);
};
 
#endif // DONTPANICENGINE_H
