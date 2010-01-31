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

#ifndef DP_DETAIL_KACTIONSTABLEMODEL_H
#define DP_DETAIL_KACTIONSTABLEMODEL_H

#include <libdontpanic/defines.hpp>
#include <libdontpanic/action.hpp>
#include <QAbstractTableModel>
#include <QStringList>

// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  namespace core
  {
    // ---------------------------------------------------------------------------------
    namespace detail
    {
      // ---------------------------------------------------------------------------------
      class KActionsTableModel : public QAbstractTableModel
      {
          // ---------------------------------------------------------------------------------
          Q_OBJECT
          // ---------------------------------------------------------------------------------
        public:
          // ---------------------------------------------------------------------------------
          KActionsTableModel ( QObject *parent = 0 );
          // ---------------------------------------------------------------------------------
        public:
          // ---------------------------------------------------------------------------------
          virtual QVariant data ( const QModelIndex& index, int role = Qt::DisplayRole ) const;
          // ---------------------------------------------------------------------------------
          virtual int columnCount ( const QModelIndex& parent = QModelIndex() ) const;
          // ---------------------------------------------------------------------------------
          virtual int rowCount ( const QModelIndex& parent = QModelIndex() ) const;
          // ---------------------------------------------------------------------------------
          virtual bool setData ( const QModelIndex& index, const QVariant& value, int role = Qt::EditRole );
          // ---------------------------------------------------------------------------------
          virtual QVariant headerData ( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;
          // ---------------------------------------------------------------------------------
          virtual bool setItemData ( const QModelIndex& index, const QMap< int, QVariant >& roles );
          // ---------------------------------------------------------------------------------
          virtual bool insertRows ( int row, int count, const QModelIndex& parent = QModelIndex() );
          // ---------------------------------------------------------------------------------
          virtual bool removeRows ( int row, int count, const QModelIndex& parent = QModelIndex() );
          // ---------------------------------------------------------------------------------
          virtual Qt::ItemFlags   flags ( const QModelIndex & index ) const;
          // ---------------------------------------------------------------------------------
        public:
          // ---------------------------------------------------------------------------------
          Action at(QModelIndex const& index) const;
          // ---------------------------------------------------------------------------------
          void set_current_day(QDate const& day);
          // ---------------------------------------------------------------------------------
        private slots:
          // ---------------------------------------------------------------------------------
          void stored(dp::Action const&);
          // ---------------------------------------------------------------------------------
          void removed(dp::Action const&);
          // ---------------------------------------------------------------------------------
        private:
          // ---------------------------------------------------------------------------------
          void init_header_data();
          // ---------------------------------------------------------------------------------
          void subscribe_to_timetracker_signals();
          // ---------------------------------------------------------------------------------
          bool is_already_known(dp::Action const&) const;
          // ---------------------------------------------------------------------------------
          void added(dp::Action const&);
          // ---------------------------------------------------------------------------------
          void updated(dp::Action const&);
          // ---------------------------------------------------------------------------------
          bool is_interesting_for_current_day(dp::Action const&);
          // ---------------------------------------------------------------------------------
          QString project_of(Action const& a) const;
          // ---------------------------------------------------------------------------------
          QString task_of(Action const& a) const;
          // ---------------------------------------------------------------------------------
          QVariant display_role(Action const& a, QModelIndex const& index) const;
          // ---------------------------------------------------------------------------------
          QVariant tooltip_role(Action const& a, QModelIndex const& index) const;
          // ---------------------------------------------------------------------------------
          QVariant edit_role(Action const& a, QModelIndex const& index) const;
          // ---------------------------------------------------------------------------------
          QVariant font_role(Action const& a, QModelIndex const& index) const;
          // ---------------------------------------------------------------------------------
        private:
          // ---------------------------------------------------------------------------------
          QStringList _M_headers;
          // ---------------------------------------------------------------------------------
          ActionList _M_actions;
          // ---------------------------------------------------------------------------------
          QDate _M_current_day;
          // ---------------------------------------------------------------------------------
      };
      // ---------------------------------------------------------------------------------
    }//detail
    // ---------------------------------------------------------------------------------
  }//core
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
#endif // DP_DETAIL_KACTIONSTABLEMODEL_H
