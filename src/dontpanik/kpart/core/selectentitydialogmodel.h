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

#ifndef DP_CORE_SELECTENTITYDIALOGMODEL_H
#define DP_CORE_SELECTENTITYDIALOGMODEL_H
#include <libdontpanic/defines.hpp>
#include <libdontpanic/uuid.h>
#include <QModelIndex>
class QSortFilterProxyModel;
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  namespace core
  {
    // ---------------------------------------------------------------------------------
    class SelectEntityTableModel;
    // ---------------------------------------------------------------------------------
    class SelectEntityDialogModel: public QObject
    {
        // ---------------------------------------------------------------------------------
        Q_OBJECT
        // ---------------------------------------------------------------------------------
      public:
        // ---------------------------------------------------------------------------------
        SelectEntityDialogModel ();
        // ---------------------------------------------------------------------------------
        virtual ~SelectEntityDialogModel();
        // ---------------------------------------------------------------------------------
      public:
        // ---------------------------------------------------------------------------------
        void init(QObject *parent);
        // ---------------------------------------------------------------------------------
      protected:
        // ---------------------------------------------------------------------------------
        virtual SelectEntityTableModel *init_source_model()=0;
        // ---------------------------------------------------------------------------------
      public:
        // ---------------------------------------------------------------------------------
        QAbstractItemModel *tableModel() const;
        virtual QString windowTitle() const = 0;
        // ---------------------------------------------------------------------------------
      public slots:
        // ---------------------------------------------------------------------------------
        void selectAll();
        void unselectAll();
        // ---------------------------------------------------------------------------------
        void select(UuidList const& ids);
        // ---------------------------------------------------------------------------------
        UuidList selection() const;        
        // ---------------------------------------------------------------------------------
      private:
        // ---------------------------------------------------------------------------------
        QSortFilterProxyModel *_M_sort_model;
        // ---------------------------------------------------------------------------------
        SelectEntityTableModel *_M_data_model;
        // ---------------------------------------------------------------------------------
    };
    // ---------------------------------------------------------------------------------
    class SelectProjectsDialogModel: public SelectEntityDialogModel
    {
      // ---------------------------------------------------------------------------------
      Q_OBJECT
      // ---------------------------------------------------------------------------------
      public:
        // ---------------------------------------------------------------------------------
        SelectProjectsDialogModel ();
      // ---------------------------------------------------------------------------------
      public:
        // ---------------------------------------------------------------------------------
        QString windowTitle() const;        
        // ---------------------------------------------------------------------------------
      protected:
        // ---------------------------------------------------------------------------------
        SelectEntityTableModel *init_source_model();      
        // ---------------------------------------------------------------------------------
    };    
    // ---------------------------------------------------------------------------------
    class SelectTasksDialogModel: public SelectEntityDialogModel
    {
      // ---------------------------------------------------------------------------------
      Q_OBJECT
      // ---------------------------------------------------------------------------------
      public:
        // ---------------------------------------------------------------------------------
        SelectTasksDialogModel ();
        // ---------------------------------------------------------------------------------
      public:
        // ---------------------------------------------------------------------------------
        QString windowTitle() const;        
        // ---------------------------------------------------------------------------------
      protected:
        // ---------------------------------------------------------------------------------
        SelectEntityTableModel *init_source_model();      
        // ---------------------------------------------------------------------------------
    };    
    // ---------------------------------------------------------------------------------
  }

}

#endif // DP_CORE_SELECTENTITYTABLEMODEL_H
