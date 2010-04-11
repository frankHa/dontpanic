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

#ifndef DP_CORE_SELECTENTITYTABLEMODELADAPTOR_H
#define DP_CORE_SELECTENTITYTABLEMODELADAPTOR_H
#include <libdontpanic/defines.hpp>
#include <libdontpanic/uuid.h>
#include <QObject>
// ---------------------------------------------------------------------------------
class QModelIndex;
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  namespace core
  {
    // ---------------------------------------------------------------------------------
    class SelectEntityTableModelAdaptor
          : public QObject
    {
        // ---------------------------------------------------------------------------------
        Q_OBJECT
        // ---------------------------------------------------------------------------------
      protected:
        // ---------------------------------------------------------------------------------
        class Entry
        {
          public:
            Entry():_M_state(Qt::Unchecked){}
            virtual ~Entry(){}
          public:
            // ---------------------------------------------------------------------------------
            int check_state() const{return _M_state;}
            void set_check_state(int state){_M_state = state;}
            virtual QString name()const =0;
            // ---------------------------------------------------------------------------------
            virtual Uuid const& id() const=0;
            // ---------------------------------------------------------------------------------
          private:
            // ---------------------------------------------------------------------------------
            int _M_state;
            // ---------------------------------------------------------------------------------
        };
        // ---------------------------------------------------------------------------------
      private:
        typedef QList<Entry*> EntryList;
      public:
        // ---------------------------------------------------------------------------------
        SelectEntityTableModelAdaptor ( QObject* parent = 0 );
        // ---------------------------------------------------------------------------------
        virtual ~SelectEntityTableModelAdaptor();
        // ---------------------------------------------------------------------------------
      public:
        // ---------------------------------------------------------------------------------
        QVariant data ( const QModelIndex& index ) const;
        int columnCount ( ) const;
        int rowCount ( ) const;
        QVariant headerData ( int column ) const;
        // ---------------------------------------------------------------------------------
        bool isCheckable ( int column ) const;
        // ---------------------------------------------------------------------------------
        int checkState ( int row ) const;
        void setCheckState ( int row, int state );
        // ---------------------------------------------------------------------------------
        UuidList checked() const;
        // ---------------------------------------------------------------------------------
        void setChecked ( UuidList const& );
        // ---------------------------------------------------------------------------------
        void checkAll();
        // ---------------------------------------------------------------------------------
        void unCheckAll();
        // ---------------------------------------------------------------------------------
      protected:
        // ---------------------------------------------------------------------------------
        void add ( Entry* entry );
        // ---------------------------------------------------------------------------------
        void addColumn ( QString const& header );
        // ---------------------------------------------------------------------------------
      private:
        // ---------------------------------------------------------------------------------
        EntryList _M_data;
        QStringList _M_headers;
        // ---------------------------------------------------------------------------------
    };
    // ---------------------------------------------------------------------------------
    class SelectProjectsTableModelAdaptor
          : public SelectEntityTableModelAdaptor
    {
        // ---------------------------------------------------------------------------------
        Q_OBJECT
        // ---------------------------------------------------------------------------------
      public:
        // ---------------------------------------------------------------------------------
        SelectProjectsTableModelAdaptor ( QObject* parent = 0 );
        // ---------------------------------------------------------------------------------
      private:
        // ---------------------------------------------------------------------------------
        void init_headers();
        // ---------------------------------------------------------------------------------
        void init_data();
        // ---------------------------------------------------------------------------------
    };
    // ---------------------------------------------------------------------------------
    class SelectTasksTableModelAdaptor
    : public SelectEntityTableModelAdaptor
    {
      // ---------------------------------------------------------------------------------
      Q_OBJECT
      // ---------------------------------------------------------------------------------
      public:
        // ---------------------------------------------------------------------------------
        SelectTasksTableModelAdaptor ( QObject* parent = 0 );
        // ---------------------------------------------------------------------------------
      private:
        // ---------------------------------------------------------------------------------
        void init_headers();
        // ---------------------------------------------------------------------------------
        void init_data();
        // ---------------------------------------------------------------------------------
    };
    // ---------------------------------------------------------------------------------
  }
  // ---------------------------------------------------------------------------------
}
// ---------------------------------------------------------------------------------
#endif //DP_CORE_SELECTENTITYTABLEMODELADAPTOR_H
