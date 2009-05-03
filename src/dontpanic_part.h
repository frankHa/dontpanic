#ifndef DONTPANICPART_H
#define DONTPANICPART_H

#include <kparts/part.h>

class QWidget;
class QPainter;
class KUrl;
class QTextEdit;
class KAboutData;
class KAction;

namespace dp{
  class dont_panic_core;
}


/**
 * This is a "Part".  It that does all the real work in a KPart
 * application.
 *
 * @short Main Part
 * @author %{AUTHOR} <%{EMAIL}>
 * @version ${APP_VERSION}
 */
class DontPanicPart : public KParts::ReadOnlyPart
{
    Q_OBJECT
public:
    /**
     * Default constructor
     */
    DontPanicPart(QWidget *parentWidget,QObject *parent, const QStringList &);

    /**
     * Destructor
     */
    virtual ~DontPanicPart();

    /**
     * This is a virtual function inherited from KParts::ReadWritePart.
     * A shell will use this to inform this Part if it should act
     * read-only
     */
    //virtual void setReadWrite(bool rw);

    /**
     * Reimplemented to disable and enable Save action
     */
    //virtual void setModified(bool modified);

    static KAboutData *createAboutData();

protected:
    /**
     * This must be implemented by each part
     */
    virtual bool openFile();

    /**
     * This must be implemented by each read-write part
     */
    virtual bool saveFile();
    KAction *save;

protected slots:
    //void fileSaveAs();

private:
    dp::dont_panic_core *_M_core;
};

#endif // DONTPANICPART_H
