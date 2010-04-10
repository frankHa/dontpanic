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

#ifndef DP_CORE_SELECTPROJECTSTABLEMODELADAPTOR_H
#define DP_CORE_SELECTPROJECTSTABLEMODELADAPTOR_H
// ---------------------------------------------------------------------------------
#include <libdontpanic/defines.hpp>
#include "selectentitytablemodeladaptor.h"
#include <libdontpanic/project.hpp>
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  namespace core
  {
    // ---------------------------------------------------------------------------------
    class SelectProjectsTableModelAdaptorPrivate;
    class SelectProjectsTableModelAdaptor
    : public SelectEntityTableModelAdaptor
    {
      class entry;
      typedef QList<entry> entry_list;
        // ---------------------------------------------------------------------------------
        Q_OBJECT
        // ---------------------------------------------------------------------------------
      public:
        // ---------------------------------------------------------------------------------
        SelectProjectsTableModelAdaptor ( QObject* parent = 0 );
        // ---------------------------------------------------------------------------------
        ~SelectProjectsTableModelAdaptor ( );
        // ---------------------------------------------------------------------------------
      public:
        // ---------------------------------------------------------------------------------
        virtual QVariant data ( const QModelIndex& index, int role=Qt::DisplayRole ) const;
        virtual int columnCount ( ) const;
        virtual int rowCount ( ) const;
        virtual QVariant headerData ( int column )const;
        bool isCheckable(QModelIndex const& index) const;
        // ---------------------------------------------------------------------------------
        void setCheckState(QModelIndex const& index, int state);
        // ---------------------------------------------------------------------------------
        virtual UuidList selected() const;
        // ---------------------------------------------------------------------------------
        virtual void setSelected(UuidList const&);
        // ---------------------------------------------------------------------------------      
      private:
        // ---------------------------------------------------------------------------------        
        SelectProjectsTableModelAdaptorPrivate *d_ptr;
        // ---------------------------------------------------------------------------------
        Q_DISABLE_COPY(SelectProjectsTableModelAdaptor);
        Q_DECLARE_PRIVATE(SelectProjectsTableModelAdaptor);
        // ---------------------------------------------------------------------------------
    };
    // ---------------------------------------------------------------------------------
  }

}

#endif // DP_CORE_SELECTPROJECTSTABLEMODELADAPTOR_H
