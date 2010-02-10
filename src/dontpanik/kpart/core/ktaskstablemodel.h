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

#ifndef KWORKTYPESTABLEMODEL_H
#define KWORKTYPESTABLEMODEL_H

#include <QAbstractTableModel>
#include <QStringList>
#include <libdontpanic/task.hpp>
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
      class KTasksTableModel : public QAbstractTableModel
      {
          // ---------------------------------------------------------------------------------
          Q_OBJECT
          // ---------------------------------------------------------------------------------
        public:
          // ---------------------------------------------------------------------------------
          KTasksTableModel ( QObject* parent = 0 );
          // ---------------------------------------------------------------------------------
        private slots:
          // ---------------------------------------------------------------------------------
          void stored(dp::Task const&);
          // ---------------------------------------------------------------------------------
          void removed(dp::Task const&);
          // ---------------------------------------------------------------------------------
        public:
          // ---------------------------------------------------------------------------------
          virtual QVariant data ( const QModelIndex& index, int role = Qt::DisplayRole ) const;
          // ---------------------------------------------------------------------------------
          virtual QVariant headerData ( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;
          // ---------------------------------------------------------------------------------
          virtual int columnCount ( const QModelIndex& parent = QModelIndex() ) const;
          // ---------------------------------------------------------------------------------
          virtual int rowCount ( const QModelIndex& parent = QModelIndex() ) const;
          // ---------------------------------------------------------------------------------
        public:
          // ---------------------------------------------------------------------------------
          Task at(QModelIndex const& index) const;
          // ---------------------------------------------------------------------------------
        private:
          // ---------------------------------------------------------------------------------
          void init_header_data();
          // ---------------------------------------------------------------------------------
          void init_tasks_list();
          // ---------------------------------------------------------------------------------
          void subscribe_to_task_manager_signals();
              // ---------------------------------------------------------------------------------
          bool is_already_known(dp::Task const&) const;
          // ---------------------------------------------------------------------------------
          void added(dp::Task const&);
          // ---------------------------------------------------------------------------------
          void updated(dp::Task const&);
          // ---------------------------------------------------------------------------------
        private:
          // ---------------------------------------------------------------------------------
          QStringList _M_headers;
          // ---------------------------------------------------------------------------------
          TaskList _M_tasks;
          // ---------------------------------------------------------------------------------
      };
      // ---------------------------------------------------------------------------------
    }//detail
    // ---------------------------------------------------------------------------------
  }
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
#endif // KWORKTYPESTABLEMODEL_H
