#ifndef DONTPANICPART_H
#define DONTPANICPART_H

#include <kparts/part.h>

class QWidget;
class QPainter;
class KUrl;
class QTextEdit;
class KAboutData;
class KAction;

namespace dp
{
  namespace core
  {
    class dont_panik_core;
  }
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
    DontPanikPart ( QWidget *parentWidget, QObject *parent, const QStringList & );

    /**
     * Destructor
     */
    virtual ~DontPanikPart();

    static KAboutData *createAboutData();

  protected:
    /**
     * This must be implemented by each part
     */
    virtual bool openFile();

  protected slots:
    //void fileSaveAs();
    void editProjects();
    void editTasks();
    void addAction();
    void stopCurrentAction();
    void continueAction();
    void startNewAction();
    void viewDayAction();
    void viewReportsAction();
    
  private:    
    void setup_actions();

  private:
    dp::core::dont_panik_core *_M_core;
};

#endif // DONTPANICPART_H
