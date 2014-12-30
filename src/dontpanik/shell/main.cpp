#include "dontpanik.hpp"
#include <QApplication>
#include <QCommandLineParser>
#include <KAboutData>
#include <KLocalizedString>

static const char author_fh[] = "Frank Habel";
static const char author_fh_email[] = "frank@bugplasma.de";
static const char version[] = "0.0.2";

int main ( int argc, char **argv )
{
//   KAboutData about ( "dontpanik", 0, ki18n ( "Don't Panik" ), version, ki18n ( description ), KAboutData::License_GPL_V3, ki18n ( "(C) 2009-2010 The Don't Panik Authors" ), KLocalizedString(), 0, author_fh_email );
//   about.setCatalogName("dontpanic");
//   about.addAuthor ( ki18n ( author_fh ), KLocalizedString(), author_fh_email );
//   KCmdLineArgs::init ( argc, argv, &about );
//
//   QCommandLineParser parser;
//   //options.add("+[URL]", ki18n( "Document to open" ));
//
//   //KLocale::setMainCatalog("dontpanic");
//
//   QApplication app;
//   parser.process(app);
//   // see if we are starting with session management
//   if ( app.isSessionRestored() )
//     RESTORE ( DontPanik )
//     else
//     {
//       // no session.. just start up normally
//       KCmdLineArgs *args = KCmdLineArgs::parsedArgs();
//
//       if ( args->count() == 0 )
//       {
//         DontPanik *widget = new DontPanik();
//         widget->show();
//       }
//       else
//       {
//         int i = 0;
//         for ( ; i < args->count(); i++ )
//         {
//           DontPanik *widget = new DontPanik;
//           widget->show();
//           // widget->load( args->url( i ) );
//         }
//       }
//       args->clear();
//     }
//
//   return app.exec();
  QApplication application ( argc, argv );

  KLocalizedString::setApplicationDomain ( "dontpanic" );
  KAboutData aboutData ( QStringLiteral ( "dontpanik" ),
                         i18n ( "Don't Panik" ),
                         version,
                         i18n ( "The KDE interface to the personal project based time tracking tool dontpanic" ),
                         KAboutLicense::GPL_V3,
                         i18n ( "(C) 2009-2014 The Don't Panik Authors" ),
                         QString(),
                         QString(),
                         author_fh_email
                       );

  aboutData.addAuthor ( i18n ( author_fh ), QString(), author_fh_email );
  KAboutData::setApplicationData ( aboutData );
  application.setWindowIcon ( QIcon::fromTheme ( "dontpanik" ) );
  QCommandLineParser parser;
  parser.addHelpOption();
  parser.addVersionOption();
  aboutData.setupCommandLine ( &parser );
  parser.process ( application );
  aboutData.processCommandLine ( &parser );

  if ( application.isSessionRestored() )
  {
    RESTORE ( DontPanik );
  }
  else
  {
    DontPanik *widget = new DontPanik();
    widget->show();
  }
  return application.exec();
}
