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

#ifndef DP_CORE_STATUSNOTIFIERITEM_H
#define DP_CORE_STATUSNOTIFIERITEM_H
#include <libdontpanic/defines.hpp>
#include <config.h>
#include <libdontpanic/dp_export.hpp>
#include <KStatusNotifierItem>
class QAction;
namespace dp
{
  // ---------------------------------------------------------------------------------
  class ActionTemplate;
  namespace core
  {
    // ---------------------------------------------------------------------------------
    class DP_EXPORT StatusNotifierItem
          : public KStatusNotifierItem
    {
        // ---------------------------------------------------------------------------------
        Q_OBJECT
        // ---------------------------------------------------------------------------------
      public:
        // ---------------------------------------------------------------------------------
        StatusNotifierItem ( QObject* parent = 0 );
        // ---------------------------------------------------------------------------------
      public slots:
        // ---------------------------------------------------------------------------------
        void onCurrentProjectChanged(QString const&);
        // ---------------------------------------------------------------------------------
        void onTodaysDurationChanged(int);
        // ---------------------------------------------------------------------------------
        void onIconChanged(QString const& icon);
        // ---------------------------------------------------------------------------------
      private slots:
        // ---------------------------------------------------------------------------------
        void on_favorite_stored(dp::ActionTemplate const& at);
        // ---------------------------------------------------------------------------------
        void on_favorite_removed(dp::ActionTemplate const& at);
        // ---------------------------------------------------------------------------------
      public:
        // ---------------------------------------------------------------------------------
        void setAssociatedWidget ( QWidget *w );
        // ---------------------------------------------------------------------------------
      private:        
        // ---------------------------------------------------------------------------------
        QAction *actionFor ( ActionTemplate const& at );
        // ---------------------------------------------------------------------------------
        void initFavoritesMenu();
        // ---------------------------------------------------------------------------------
        void initTooltip();
        // ---------------------------------------------------------------------------------
        void populateFavoritesMenu();
        // ---------------------------------------------------------------------------------
      private:
        // ---------------------------------------------------------------------------------
        void init();
        // ---------------------------------------------------------------------------------
        QMenu *_M_fav_menu;
        // ---------------------------------------------------------------------------------
    };
    // ---------------------------------------------------------------------------------
  }
  // ---------------------------------------------------------------------------------
}
// ---------------------------------------------------------------------------------
#endif // DP_CORE_STATUSNOTIFIERITEM_H
