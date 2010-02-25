#ifndef ACTIONITEM_H
#define ACTIONITEM_H

#include <QObject>
#include <QGraphicsWidget>
#include "detail/action.h"

class QGraphicsLinearLayout;
class QGraphicsSceneHoverEvent;
class KAction;
namespace Plasma
{
  class Label;
  class Animation;
}

namespace dp
{
namespace plasma
{
namespace applet
{
  class PlasmaDontPanic;

class ActionItem: public QGraphicsWidget
{
    Q_OBJECT

public:
    ActionItem(QGraphicsWidget *parent, PlasmaDontPanic *applet);

    ~ActionItem();
    
  public slots:
    void setAction(detail::Action const&);
    
  public:
    void setHovered(bool hovered);
    
  protected:
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent * event);
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent * event);
    
  private:
    void setActionDescription(detail::Action const& );
    void expand();
    void collapse();
    bool isCollapsed() const;
    void initPossibleActionsFor(detail::Action const&);
    void removePossibleActions();
    void addPossibleActionsFor(detail::Action const&);
    void addPossibleAction(KAction *action);
    
    PlasmaDontPanic *applet();
  private:
    PlasmaDontPanic *_M_applet;
    detail::Action _M_current_action;
    Plasma::Label *_M_action_description;
    Plasma::Label *_M_possible_actions;
    QGraphicsLinearLayout *_M_tree_layout;
    QGraphicsWidget *_M_actions_widget;
    QGraphicsLinearLayout * _M_actions_layout;
    Plasma::Animation *_M_label_fade;
    bool _M_hovered;

};
}
}

}
#endif
