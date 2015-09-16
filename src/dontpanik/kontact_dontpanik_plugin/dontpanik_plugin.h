#ifndef DONTPANIK_PLUGIN_H
#define DONTPANIK_PLUGIN_H

#include <KontactInterface/Plugin>
#include <KParts/Part>

class DontPanikPlugin : public KontactInterface::Plugin
{
  Q_OBJECT
  
  public:
    DontPanikPlugin( KontactInterface::Core *core, const QVariantList & );
    ~DontPanikPlugin();
    
    virtual void readProperties( const KConfigGroup &config );
    virtual void saveProperties( KConfigGroup &config );
    
  private slots:
    void showPart();
    
  protected:
    KParts::ReadOnlyPart *createPart();
};

#endif