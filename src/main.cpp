#include "dontpanic.h"
#include <kapplication.h>
#include <kaboutdata.h>
#include <kcmdlineargs.h>
#include <klocale.h>

static const char description[] =
    I18N_NOOP("A personal project centered time tracking tool");

static const char author_fh[] = "Frank Habel";
static const char author_fh_email[] = "frank@bugplasma.de";
static const char version[] = "0.0.1";

int main(int argc, char **argv)
{
    KAboutData about("dontpanic", 0, ki18n("Don't Panic"), version, ki18n(description), KAboutData::License_GPL, ki18n("(C) 2008 %{AUTHOR}"), KLocalizedString(), 0, author_fh_email);
    about.addAuthor( ki18n(author_fh), KLocalizedString(), author_fh_email );
    KCmdLineArgs::init(argc, argv, &about);

    KCmdLineOptions options;
    options.add("+[URL]", ki18n( "Document to open" ));
    KCmdLineArgs::addCmdLineOptions( options );
    KApplication app;

    // see if we are starting with session management
    if (app.isSessionRestored())
        RESTORE(DontPanic)
    else
    {
        // no session.. just start up normally
        KCmdLineArgs *args = KCmdLineArgs::parsedArgs();

        if ( args->count() == 0 )
        {
        DontPanic *widget = new DontPanic;
        widget->show();
        }
        else
        {
            int i = 0;
            for (; i < args->count(); i++ )
            {
                DontPanic *widget = new DontPanic;
                widget->show();
                widget->load( args->url( i ) );
            }
        }
        args->clear();
    }

    return app.exec();
}
