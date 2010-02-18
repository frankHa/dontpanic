#ifndef ACTIONITEM_H
#define ACTIONITEM_H

#include <QObject>
#include <QGraphicsWidget>
#include "detail/action.h"

class QGraphicsLinearLayout;
namespace Plasma
{
  class Label;
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
    
    
  private:
    void setActionDescription(detail::Action const& );
    
  private:
    detail::Action _M_current_action;
    Plasma::Label *_M_action_description;
    QGraphicsLinearLayout *_M_tree_layout;
      

};
}
}

}
#endif
