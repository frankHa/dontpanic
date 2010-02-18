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
}


namespace dp {

namespace plasma {

namespace applet {

  class PlasmaDontPanic;
class Dialog: public QObject
{
  Q_OBJECT
  public:
  Dialog(PlasmaDontPanic *dp, QObject *parent = 0);
  
  public:
      QGraphicsWidget *dialog();
      
  private slots:
    void on_current_duration_changed(int);
    void on_current_action_changed(detail::Action const&);
    void on_favorite_added(detail::Favorite const&);
    void on_favorite_removed(detail::Favorite const&);
    void on_favorite_updated(detail::Favorite const&);
    
    
  private:
    void build_dialog();
    QGraphicsWidget* button_for(KAction *action);
    QGraphicsWidget* switch_activity();
    void rebuild_favorites_menu();
  private: 
    PlasmaDontPanic *_M_dp_applet;
    Plasma::Label *_M_main_label;
    Plasma::Label *_M_duration_label;
    Plasma::Label *_M_current_action_label;
    QGraphicsWidget* _M_widget;
    Plasma::PushButton *_M_switch_activity_button;
    //QMenu *_M_favorites_menu;
};

}

}

}

#endif // DP_PLASMA_APPLET_DIALOG_H
