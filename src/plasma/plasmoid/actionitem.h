#ifndef ACTIONITEM_H
#define ACTIONITEM_H

#include <QObject>
#include <QGraphicsWidget>
#include "detail/action.h"

class QGraphicsLinearLayout;
class QGraphicsSceneHoverEvent;
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

class ActionItem: public QGraphicsWidget
{
    Q_OBJECT

public:
    ActionItem(QGraphicsWidget *parent = 0);

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
    
  private:
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
