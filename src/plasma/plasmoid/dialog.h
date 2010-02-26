/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) <year>  <name of author>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef DP_PLASMA_APPLET_DIALOG_H
#define DP_PLASMA_APPLET_DIALOG_H

#include <QObject>

#include "detail/action.h"
#include "detail/favorite.h"
class QGraphicsWidget;
class KAction;
class QMenu;
namespace Plasma
{
  class Label;
  class PushButton;
  class IconWidget;
}


namespace dp {

namespace plasma {

namespace applet {

  class PlasmaDontPanic;
  class ActionItem;
class Dialog: public QObject
{
  Q_OBJECT
  public:
  Dialog(PlasmaDontPanic *dp, QObject *parent = 0);
  
  public:
      QGraphicsWidget *dialog();
      
  private slots:
    void on_current_duration_changed(int);
    
  private:
    void build_dialog();
    QGraphicsWidget* switch_activity();
    ActionItem *createActionItem(QGraphicsWidget *parent );
  private: 
    PlasmaDontPanic *_M_dp_applet;
    Plasma::Label *_M_main_label;
    Plasma::Label *_M_duration_label;
    QGraphicsWidget* _M_widget;
    Plasma::PushButton *_M_switch_activity_button;
    Plasma::IconWidget *_M_icon;
private slots:
    void updateIcon(QString const&);
};

}

}

}

#endif // DP_PLASMA_APPLET_DIALOG_H
