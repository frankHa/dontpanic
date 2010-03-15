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
#include "statusnotifieritem.h"
#ifdef DP_BUILD_TRAY_ICON_SUPPORT
#include "context.h"
#include "actiontemplateaction.h"
#include <libdontpanic/durationformatter.h>
#include <KMenu>

namespace dp
{
  // ---------------------------------------------------------------------------------
  namespace core
  {
    // ---------------------------------------------------------------------------------
    StatusNotifierItem::StatusNotifierItem ( QObject* parent )
        : KStatusNotifierItem ( "dontpanik_part", parent )
    {
      init();
    }

    // ---------------------------------------------------------------------------------
    void StatusNotifierItem::setAssociatedWidget ( QWidget* w )
    {
      KStatusNotifierItem::setAssociatedWidget ( w );
      connect ( this, SIGNAL ( activateRequested ( bool, QPoint ) ), w, SLOT ( setVisible ( bool ) ) );
    }

    // ---------------------------------------------------------------------------------
    void StatusNotifierItem::initTooltip()
    {
      setToolTipIconByName ( "dontpanik" );
      setToolTipTitle ( "Don't Panik" );
    }
    // ---------------------------------------------------------------------------------
    void StatusNotifierItem::onCurrentProjectChanged ( QString const& project_description )
    {
      kDebug() << project_description;
      setToolTipSubTitle ( project_description );
    }
    // ---------------------------------------------------------------------------------
    void StatusNotifierItem::onTodaysDurationChanged ( int duration )
    {
      kDebug() << duration;
      setToolTipTitle ( duration_formatter().format ( duration ) );
    }
    // ---------------------------------------------------------------------------------
    void StatusNotifierItem::onIconChanged ( QString const& icon )
    {
      kDebug() << icon;
      setIconByName ( icon );
      setToolTipIconByName ( icon );
    }
    // ---------------------------------------------------------------------------------
    // private stuff:
    // ---------------------------------------------------------------------------------
    void StatusNotifierItem::init()
    {
      setIconByName ( "dontpanik" );
      KMenu *menu = contextMenu();
      menu->addAction ( context()->globalActions()->action ( "start_new_action" ) );
      menu->addAction ( context()->globalActions()->action ( "stop_current_action" ) );
      menu->addAction ( context()->globalActions()->action ( "continue_action" ) );
      initFavoritesMenu();
      initTooltip();
      connect ( context()->actionTemplateManager(), SIGNAL ( stored ( dp::ActionTemplate ) ), this, SLOT ( on_favorite_stored ( dp::ActionTemplate const&) ) );
      connect ( context()->actionTemplateManager(), SIGNAL ( removed ( dp::ActionTemplate ) ), this, SLOT ( on_favorite_removed ( dp::ActionTemplate const&) ) );
    }
    // ---------------------------------------------------------------------------------
    void StatusNotifierItem::initFavoritesMenu()
    {
      KMenu *menu = contextMenu();
      menu->addSeparator();
      _M_fav_menu = new KMenu ( i18n ( "switch activity to..." ), menu );
      populateFavoritesMenu();
      menu->addMenu ( _M_fav_menu );
    }
    // ---------------------------------------------------------------------------------
    void StatusNotifierItem::populateFavoritesMenu()
    {
      _M_fav_menu->clear();
      foreach ( ActionTemplate const& at, context()->actionTemplateManager()->allActionTemplates() )
      {
        _M_fav_menu->addAction ( actionFor ( at ) );
      }
    }
    // ---------------------------------------------------------------------------------
    KAction* StatusNotifierItem::actionFor ( ActionTemplate const& a )
    {
      ActionTemplateAction * ata = new ActionTemplateAction ( this );
      ata->setFavorite ( a );
      connect ( ata, SIGNAL ( triggered ( ActionTemplate ) ), context()->timeTracker(), SLOT ( startActionFromTemplate ( ActionTemplate const& ) ) );
      return ata;
    }
    // ---------------------------------------------------------------------------------
    void StatusNotifierItem::on_favorite_stored ( ActionTemplate const& at )
    {
      populateFavoritesMenu();
    }
    // ---------------------------------------------------------------------------------
    void StatusNotifierItem::on_favorite_removed ( ActionTemplate const& at )
    {
      populateFavoritesMenu();
    }
    // ---------------------------------------------------------------------------------
  }
}
#endif //DP_BUILD_TRAY_ICON_SUPPORT
