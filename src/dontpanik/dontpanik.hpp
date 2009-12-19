#ifndef DONTPANIC_H
#define DONTPANIC_H

#include <kparts/mainwindow.h>

/**
 * This is the application "Shell".  It has a menubar, toolbar, and
 * statusbar but relies on the "Part" to do all the real work.
 *
 * @short Application Shell
 * @author ${AUTHOR} <${EMAIL}>
 * @version ${APP_VERSION}
 */
class DontPanik : public KParts::MainWindow
{
    Q_OBJECT
public:
    /**
     * Default Constructor
     */
    DontPanik();

    /**
     * Default Destructor
     */
    virtual ~DontPanik();

    /**
     * Use this method to load whatever file/URL you have
     */
    //void load(const KUrl& url);

protected:
    /**
     * This method is called when it is time for the app to save its
     * properties for session management purposes.
     */
    void saveProperties(KConfigGroup &);

    /**
     * This method is called when this app is restored.  The KConfig
     * object points to the session management config file that was saved
     * with @ref saveProperties
     */
    void readProperties(const KConfigGroup &);

private slots:
    //void fileNew();
    //void fileOpen();
    void optionsConfigureKeys();
    void optionsConfigureToolbars();

    //void applyNewToolbarConfig();

private:
    void setupActions();

private:
    KParts::ReadOnlyPart *_M_part;
};

#endif // DONTPANIC_H
