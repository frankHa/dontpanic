#include "dontpanik_plugin.h"

#include <dontpanik_part.hpp>

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
  
  connect( part, SIGNAL(showPart()), this, SLOT(showPart()) );
  
  return part;
}

void DontPanikPlugin::readProperties( const KConfigGroup &config )
{
//   if ( part() )
//   {
//     DontPanikPart *myPart = static_cast<DontPanikPart*>( part() );
//   }
}

void DontPanikPlugin::saveProperties( KConfigGroup &config )
{
//   if ( part() )
//   {
//     DontPanikPart *myPart = static_cast<DontPanikPart*>( part() );
//   }
}

void DontPanikPlugin::showPart()
{
  core()->selectPlugin(this);
}

#include "dontpanik_plugin.moc"