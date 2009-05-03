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
  class dont_panik_core;
}


/**
 * This is a "Part".  It that does all the real work in a KPart
 * application.
 *
 * @short Main Part
 * @author %{AUTHOR} <%{EMAIL}>
 * @version ${APP_VERSION}
 */
class DontPanikPart : public KParts::ReadOnlyPart
{
    Q_OBJECT
public:
    /**
     * Default constructor
     */
    DontPanikPart(QWidget *parentWidget,QObject *parent, const QStringList &);

    /**
     * Destructor
     */
    virtual ~DontPanikPart();

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
    dp::dont_panik_core *_M_core;
};

#endif // DONTPANICPART_H
