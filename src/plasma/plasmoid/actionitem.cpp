#include "actionitem.h"
#include "detail/action.h"
#include <libdontpanic/durationformatter.h>
#include <Plasma/Label>
#include <Plasma/Animator>
#include <Plasma/Animation>
#include <QGraphicsLinearLayout>
#include <QGraphicsSceneHoverEvent>

namespace dp
{
namespace plasma
{
namespace applet
{
static const int MARGIN = 3;
ActionItem::ActionItem(QGraphicsWidget *parent)
        :QGraphicsWidget(parent)
        , _M_current_action()
        , _M_action_description(0)
        , _M_possible_actions(0)
        ,_M_label_fade(0)
        ,_M_hovered(false)
{
    this->setAcceptHoverEvents(true);
    setCacheMode(DeviceCoordinateCache);
    setZValue(0);
    setContentsMargins(MARGIN, MARGIN, MARGIN, MARGIN);
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    _M_action_description = new Plasma::Label(this);
    _M_possible_actions = new Plasma::Label(this);
    _M_tree_layout = new QGraphicsLinearLayout(Qt::Vertical, this);
    QGraphicsLinearLayout *info = new QGraphicsLinearLayout(Qt::Vertical);
    info->addItem(_M_action_description);
    info->addItem(_M_possible_actions);
    //_M_possible_actions->setText("switch activity to...");
    _M_possible_actions->setOpacity(0);
    _M_tree_layout->addItem(info);
    this->setLayout(_M_tree_layout);
    setAction(_M_current_action);
}

ActionItem::~ActionItem() {}

void ActionItem::setAction(const detail::Action& action)
{
    _M_current_action = action;
    setActionDescription(_M_current_action);
}


void ActionItem::setActionDescription(detail::Action const& action)
{
    if (action.active)
    {
        QString tooltip = i18n("Currently working on: \nProject: %1\nTask: %2\nRunning since: %3\nCurrent duration: %4")
                          .arg(action.project)
                          .arg(action.task)
                          .arg(action.start.time().toString(Qt::SystemLocaleShortDate))
                          .arg(duration_formatter().format(action.duration));
        _M_action_description->setText(tooltip);
    }
    else
    {
        _M_action_description->setText(i18n("There is currently no running activity..."));
    }
}

void ActionItem::setHovered(bool hovered)
{
    if (hovered == _M_hovered) {
        return;
    }
    _M_hovered = hovered;
    
    int targetOpacity = (hovered)?100:0;
    if (!_M_label_fade) {
        _M_label_fade = Plasma::Animator::create(Plasma::Animator::FadeAnimation, this);

        _M_label_fade->setTargetWidget(_M_possible_actions);
    }
    _M_label_fade->setProperty("targetOpacity", targetOpacity);
    qreal currentOpacity = _M_action_description->opacity();
    _M_label_fade->setProperty("startOpacity", currentOpacity);
    _M_label_fade->start();

}
void ActionItem::hoverEnterEvent(QGraphicsSceneHoverEvent * event)
{
    setHovered(true);
}
void ActionItem::hoverLeaveEvent(QGraphicsSceneHoverEvent * event)
{
    setHovered(false);
}
}
}
}
#include "actionitem.moc"
