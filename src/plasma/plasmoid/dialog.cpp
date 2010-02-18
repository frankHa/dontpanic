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

#include "dialog.h"
#include "plasma-dontpanic.h"
#include "actionitem.h"
#include <libdontpanic/durationformatter.h>
#include <QGraphicsLinearLayout>

//Plasma includes
#include <Plasma/Label>
#include <Plasma/IconWidget>
#include <Plasma/Separator>
#include <Plasma/PushButton>
#include <KIconLoader>
#include <KPushButton>
#include <QLabel>
#include <KAction>
#include <QMenu>

namespace dp
{
namespace plasma
{
namespace applet
{
Dialog::Dialog(PlasmaDontPanic *dp, QObject *parent)
        :QObject(parent)
        , _M_dp_applet(dp)
        , _M_main_label(0)
        , _M_duration_label(0)
        , _M_widget(0)
{
    build_dialog();

    connect(dp, SIGNAL(currentDurationChanged(int)), this, SLOT(on_current_duration_changed(int)));
    connect(dp, SIGNAL(favorite_added(detail::Favorite const&)), this, SLOT(on_favorite_added(detail::Favorite const&)));
    connect(dp, SIGNAL(favorite_removed(detail::Favorite const&)), this, SLOT(on_favorite_removed(detail::Favorite const&)));
    connect(dp, SIGNAL(favorite_updated(detail::Favorite const&)), this, SLOT(on_favorite_updated(detail::Favorite const&)));
}

QGraphicsWidget* Dialog::dialog()
{
    return _M_widget;
}
// ---------------------------------------------------------------------------------
// private stuff:
// ---------------------------------------------------------------------------------
void Dialog::build_dialog()
{
    _M_widget = new QGraphicsWidget(_M_dp_applet);
    _M_widget->setFocusPolicy(Qt::ClickFocus);

    QGraphicsLinearLayout *l_layout = new QGraphicsLinearLayout(Qt::Vertical, _M_widget);
    l_layout->setSpacing(0);
    Plasma::IconWidget *icon = new Plasma::IconWidget(_M_widget);
    icon->setIcon(KIcon("dontpanik"));
    icon->setMaximumHeight(KIconLoader::SizeMedium);
    icon->setMinimumHeight(KIconLoader::SizeMedium);
    icon->setAcceptHoverEvents(false);
    _M_main_label = new Plasma::Label(_M_widget);
    _M_main_label->setMaximumHeight(KIconLoader::SizeMedium);
    _M_main_label->nativeWidget()->setWordWrap(false);
    _M_main_label->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    _M_main_label->setText(i18n("Don't Panic"));

    QGraphicsLinearLayout *l_layout2 = new QGraphicsLinearLayout;
    l_layout2->setSpacing(0);
    l_layout2->setOrientation(Qt::Horizontal);
    l_layout2->addItem(icon);
    l_layout2->addItem(_M_main_label);
    l_layout2->addStretch();
    QGraphicsWidget *titleWidget = new QGraphicsWidget();
    titleWidget->setLayout(l_layout2);
    l_layout->addItem(titleWidget);
    l_layout->addItem(new Plasma::Separator());



    _M_duration_label = new Plasma::Label(_M_widget);
    _M_duration_label->setAlignment(Qt::AlignHCenter);
    _M_duration_label->setScaledContents(true);
    l_layout->addItem(_M_duration_label);
    
    l_layout->addItem(createActionItem(_M_widget));

    QGraphicsLinearLayout *l_blayout = new QGraphicsLinearLayout;
    l_blayout->setSpacing(0);
    l_blayout->setOrientation(Qt::Horizontal);
    l_blayout->addStretch();
    l_blayout->addItem(button_for(_M_dp_applet->start_new_action()));
    l_blayout->addItem(button_for(_M_dp_applet->stop_current_action()));
    l_blayout->addItem(button_for(_M_dp_applet->resume_last_action()));
    l_blayout->addStretch();
    QGraphicsWidget *bWidget = new QGraphicsWidget();
    bWidget->setLayout(l_blayout);

    l_layout->addItem(bWidget);

    l_layout->addItem(switch_activity());
    l_layout->addStretch();
    _M_widget->setLayout(l_layout);
    _M_widget->setMinimumSize(250, 300);
}
// ---------------------------------------------------------------------------------
ActionItem *Dialog::createActionItem(QGraphicsWidget *parent)
{
  ActionItem *item = new ActionItem(parent);
  connect(_M_dp_applet, SIGNAL(currentActionChanged(detail::Action const&)), item, SLOT(setAction(detail::Action const&)));
  return item;
}
// ---------------------------------------------------------------------------------
QGraphicsWidget* Dialog::button_for(KAction *action)
{
    Plasma::IconWidget *b = new Plasma::IconWidget(_M_widget);
    b->setAction(action);
    return b;
}
// ---------------------------------------------------------------------------------
QGraphicsWidget* Dialog::switch_activity()
{
    _M_switch_activity_button = new Plasma::PushButton(_M_widget);
    _M_switch_activity_button->setText(i18n("switch activity to..."));
    rebuild_favorites_menu();
    return _M_switch_activity_button;

}
// ---------------------------------------------------------------------------------
void Dialog::on_current_duration_changed(int duration)
{
    QString dur = QString("<b>%1<b>").arg(duration_formatter().format(duration));
    _M_duration_label->setText(dur);
}
// ---------------------------------------------------------------------------------
void Dialog::on_favorite_added(detail::Favorite const& fav)
{
    rebuild_favorites_menu();
}
void Dialog::on_favorite_removed(detail::Favorite const&)
{
    rebuild_favorites_menu();
}
void Dialog::on_favorite_updated(detail::Favorite const& fav)
{
    rebuild_favorites_menu();
}
// ---------------------------------------------------------------------------------
void Dialog::rebuild_favorites_menu()
{
  detail::FavoriteList favList = _M_dp_applet->favorites();
  QMenu *oldmenu = _M_switch_activity_button->nativeWidget()->menu();
  QMenu *newMenu = new QMenu(_M_switch_activity_button->nativeWidget());
      
  qSort(favList);
  for(int i=0;i<favList.length(); ++i)
  {
    newMenu->addAction(_M_dp_applet->action_for(favList.value(i)));
  }
  _M_switch_activity_button->nativeWidget()->setMenu(newMenu);
  if(oldmenu != 0)
  {
   delete oldmenu; 
  }
}
// ---------------------------------------------------------------------------------
}
}
}

