#include "actiontemplateaction.h"
#include <KIcon>
namespace dp
{
  namespace plasma
  {
    namespace applet
    {
      namespace detail
      {
ActionTemplateAction::ActionTemplateAction(QObject* parent)
: KAction(parent)
,_M_template(NullActionTemplate())
{
  connect(this, SIGNAL(triggered()), this, SLOT(on_triggered()));
}
ActionTemplateAction& ActionTemplateAction::setActionTemplate(const dp::ActionTemplate& templ)
{
  _M_template = templ;
  setIcon(KIcon(templ.icon()));
  setText(templ.name());
  return *this;
}

void ActionTemplateAction::on_triggered()
{
  emit triggered(_M_template);
}


ActionTemplate const& ActionTemplateAction::actionTemplate() const
{
  return _M_template;
}

      }
    }
  }
}