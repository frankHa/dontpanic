#include "dontpanik_plugin.h"

#include <KontactInterface/Core>
#include <KontactInterface/Plugin>

#include <KActionCollection>
#include <QIcon>

EXPORT_KONTACT_PLUGIN( DontPanikPlugin, dontpanik )

DontPanikPlugin::DontPanikPlugin( KontactInterface::Core *core, const QVariantList & )
: KontactInterface::Plugin( core, core, "DontPanik" )
{
  setComponentName( QStringLiteral("DontPanik"), QStringLiteral("DontPanik") );
}

DontPanikPlugin::~DontPanikPlugin()
{
}

KParts::ReadOnlyPart *DontPanikPlugin::createPart()
{
  KParts::ReadOnlyPart *part = loadPart();
  return part;
}

#include "dontpanik_plugin.moc"