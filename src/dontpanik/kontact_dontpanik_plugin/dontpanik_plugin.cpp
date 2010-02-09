#include "dontpanik_plugin.h"

#include <dontpanik_part.hpp>

#include <kontactinterface/core.h>
#include <kontactinterface/plugin.h>

#include <kactioncollection.h>
#include <kgenericfactory.h>
#include <kicon.h>
#include <kparts/componentfactory.h>

EXPORT_KONTACT_PLUGIN( DontPanikPlugin, dontpanik )

DontPanikPlugin::DontPanikPlugin( KontactInterface::Core *core, const QVariantList & )
: KontactInterface::Plugin( core, core, "DontPanik" )
{
  setComponentData( KontactPluginFactory::componentData() );
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
  if ( part() )
  {
    DontPanikPart *myPart = static_cast<DontPanikPart*>( part() );
  }
}

void DontPanikPlugin::saveProperties( KConfigGroup &config )
{
  if ( part() )
  {
    DontPanikPart *myPart = static_cast<DontPanikPart*>( part() );
  }
}

void DontPanikPlugin::showPart()
{
  core()->selectPlugin(this);
}