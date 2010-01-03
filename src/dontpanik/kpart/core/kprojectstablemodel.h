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

#ifndef KPROJECTSTABLEMODEL_H
#define KPROJECTSTABLEMODEL_H

#include <QAbstractTableModel>
#include <QStringList>
#include <libdontpanic/project.hpp>

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
      class KProjectsTableModel : public QAbstractTableModel
      {
          // ---------------------------------------------------------------------------------
          Q_OBJECT
          // ---------------------------------------------------------------------------------
        public:
          // ---------------------------------------------------------------------------------
          KProjectsTableModel ( QObject* parent = 0 );
          // ---------------------------------------------------------------------------------
	private slots:
	  // ---------------------------------------------------------------------------------
	  void stored(dp::Project const&);
	  // ---------------------------------------------------------------------------------
	  void removed(dp::Project const&);
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
        private:
          // ---------------------------------------------------------------------------------
          void init_header_data();
          // ---------------------------------------------------------------------------------
          void init_projects_list();
	  // ---------------------------------------------------------------------------------
	  void subscribe_to_project_manager_signals();
          // ---------------------------------------------------------------------------------
	  bool is_already_known(dp::Project const&) const;
	  // ---------------------------------------------------------------------------------
	  void added(dp::Project const&);
	  // ---------------------------------------------------------------------------------
	  void updated(dp::Project const&);
	  // ---------------------------------------------------------------------------------
        private:
          // ---------------------------------------------------------------------------------
          QStringList _M_headers;
	  // ---------------------------------------------------------------------------------
	  ProjectList _M_projects;
          // ---------------------------------------------------------------------------------
      };
      // ---------------------------------------------------------------------------------
    }//detail
    // ---------------------------------------------------------------------------------
  }
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
#endif // KPROJECTSTABLEMODEL_H
