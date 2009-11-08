#include <KCmdLineArgs>
#include <KCmdLineOptions>
#include <KAboutData>
#include <KApplication>

static const char description[] =
    I18N_NOOP("simple utility to import original TIP configurations into your DontPanic installation");

static const char author_fh[] = "Frank Habel";
static const char author_fh_email[] = "frank@bugplasma.de";
static const char version[] = "0.0.1";

int main(int argc, char **argv)
{
    KAboutData about("dp_tipimport", 0, ki18n("TIP import"), version, ki18n(description), KAboutData::License_GPL_V3, ki18n("(C) 2009 The Don't Panic Authors"), KLocalizedString(), 0, author_fh_email);
    about.addAuthor( ki18n(author_fh), KLocalizedString(), author_fh_email );
    KCmdLineOptions options;
    options.add("+tipdir <directory>", ki18n("The directory that contains the TIP configuration files."));

    KCmdLineArgs::addCmdLineOptions(options, ki18n("TIP import"), "tip");

    KCmdLineArgs::init(argc, argv, &about);
    KApplication app;
}
