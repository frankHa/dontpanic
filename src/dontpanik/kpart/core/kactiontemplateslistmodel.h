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

#ifndef KACTIONTEMPLATESLISTMODEL_H
#define KACTIONTEMPLATESLISTMODEL_H

#include <QAbstractListModel>
#include <QStringList>
#include <libdontpanic/actiontemplate.hpp>

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
      class KActionTemplatesListModel: public QAbstractListModel
      {
          // ---------------------------------------------------------------------------------
          Q_OBJECT
          // ---------------------------------------------------------------------------------
        public:
          // ---------------------------------------------------------------------------------
          KActionTemplatesListModel ( QObject* parent = 0 );
          // ---------------------------------------------------------------------------------
	private slots:
	  // ---------------------------------------------------------------------------------
	  void stored(dp::ActionTemplate const&);
	  // ---------------------------------------------------------------------------------
	  void removed(dp::ActionTemplate const&);
	  // ---------------------------------------------------------------------------------
        public:
          // ---------------------------------------------------------------------------------
          virtual QVariant data ( const QModelIndex& index, int role = Qt::DisplayRole ) const;
          // ---------------------------------------------------------------------------------
          virtual QVariant headerData ( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;
          // ---------------------------------------------------------------------------------
          virtual int rowCount ( const QModelIndex& parent = QModelIndex() ) const;
          // ---------------------------------------------------------------------------------
          ActionTemplate at(QModelIndex const& index);
          // ---------------------------------------------------------------------------------
        private:
          // ---------------------------------------------------------------------------------
          void init_header_data();
          // ---------------------------------------------------------------------------------
          void init_action_templates_list();
	  // ---------------------------------------------------------------------------------
	  void subscribe_to_action_template_manager_signals();
          // ---------------------------------------------------------------------------------
	  bool is_already_known(dp::ActionTemplate const&) const;
	  // ---------------------------------------------------------------------------------
	  void added(dp::ActionTemplate const&);
	  // ---------------------------------------------------------------------------------
	  void updated(dp::ActionTemplate const&);
	  // ---------------------------------------------------------------------------------
        private:
          // ---------------------------------------------------------------------------------
          QStringList _M_headers;
	  // ---------------------------------------------------------------------------------
	  TemplateList _M_projects;
          // ---------------------------------------------------------------------------------
      };
      // ---------------------------------------------------------------------------------
    }//detail
    // ---------------------------------------------------------------------------------
  }
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
#endif // KACTIONTEMPLATESLISTMODEL_H
