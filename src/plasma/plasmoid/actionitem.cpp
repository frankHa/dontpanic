#include "actionitem.h"
#include "detail/action.h"
#include <libdontpanic/durationformatter.h>
#include <Plasma/Label>
#include <QGraphicsLinearLayout>

namespace dp
{
namespace plasma
{
namespace applet
{
ActionItem::ActionItem(QGraphicsWidget *parent)
:QGraphicsWidget(parent)
, _M_current_action()
, _M_action_description(0)
{
  _M_action_description = new Plasma::Label(this);
  _M_tree_layout = new QGraphicsLinearLayout(Qt::Vertical, this);
  QGraphicsLinearLayout *l = new QGraphicsLinearLayout(Qt::Horizontal);
  l->addItem(_M_action_description);
  _M_tree_layout->addItem(l);
  this->setLayout(_M_tree_layout);
  setAction(_M_current_action);
}

ActionItem::~ActionItem(){}

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
}
}
}
#include "actionitem.moc"
