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
        ,_M_favorite(Favorite())
{
    connect(this, SIGNAL(triggered()), this, SLOT(on_triggered()));
}
ActionTemplateAction& ActionTemplateAction::setFavorite(const Favorite& fav)
{
    _M_favorite = fav;
    setIcon(KIcon(fav.icon));
    setText(fav.name);
    return *this;
}

void ActionTemplateAction::on_triggered()
{
    emit triggered(_M_favorite);
}


Favorite const& ActionTemplateAction::favorite() const
{
    return _M_favorite;
}

}
}
}
}
