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

#include "selectprojectstablemodeladaptor.h"
#include "context.h"
#include <QVariant>
#include <QModelIndex>
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  namespace core
  {
    // ---------------------------------------------------------------------------------
    class Entry
    {
      public:
        Entry ( Project const& p ) : check_state ( Qt::Unchecked ), project ( p ) {}

        int check_state;
        Project project;
    };
    // ---------------------------------------------------------------------------------
    class SelectProjectsTableModelAdaptorPrivate
    {
        typedef QList<Entry*> EntryList;
      public:
        // ---------------------------------------------------------------------------------
        SelectProjectsTableModelAdaptorPrivate();
        ~SelectProjectsTableModelAdaptorPrivate(){qDeleteAll(_M_entries);}
        // ---------------------------------------------------------------------------------
      public:
        // ---------------------------------------------------------------------------------
        QVariant data ( const QModelIndex& index, int role ) const;
        int columnCount ( ) const;
        int rowCount ( ) const;
        QVariant headerData ( int column ) const;
        bool isCheckable(QModelIndex const& index) const;
        // ---------------------------------------------------------------------------------
        void setCheckState(QModelIndex const& index, int state);
        // ---------------------------------------------------------------------------------
        UuidList selected() const;
        // ---------------------------------------------------------------------------------
        void setSelected ( UuidList const& );
        // ---------------------------------------------------------------------------------
      private:
        // ---------------------------------------------------------------------------------
        void init_headers();
        // ---------------------------------------------------------------------------------
        void init_projects_list();
        // ---------------------------------------------------------------------------------
      private:
        // ---------------------------------------------------------------------------------
        QStringList _M_headers;
        // ---------------------------------------------------------------------------------
        EntryList _M_entries;
        // ---------------------------------------------------------------------------------
    };
    // ---------------------------------------------------------------------------------
    // SelectProjectTableModelAdaptorPrivate:
    // ---------------------------------------------------------------------------------
    SelectProjectsTableModelAdaptorPrivate::SelectProjectsTableModelAdaptorPrivate()
    {
      init_headers();
      init_projects_list();
    }
    // ---------------------------------------------------------------------------------
    QVariant SelectProjectsTableModelAdaptorPrivate::data ( const QModelIndex& index, int role ) const
    {
      if ( index.row() >= rowCount() ) return QVariant();
      Entry const* e ( _M_entries.at ( index.row() ) );
      if(index.column() == 0&& role == Qt::CheckStateRole)
      {
        return e->check_state;
      }
      if(index.column() == 0&& role == Qt::EditRole)
      {
        return e->check_state;
        //if(e.check_state == Qt::Checked) return true;
        //return false;        
      }
      if(index.column()==1 && role==Qt::DisplayRole)
      {
        return e->project.name();
      }
      return QVariant();

    }
    // ---------------------------------------------------------------------------------
    int SelectProjectsTableModelAdaptorPrivate::columnCount ( ) const
    {
      return _M_headers.count();
    }
    // ---------------------------------------------------------------------------------
    int SelectProjectsTableModelAdaptorPrivate::rowCount ( ) const
    {
      return _M_entries.size();
    }
    // ---------------------------------------------------------------------------------
    QVariant SelectProjectsTableModelAdaptorPrivate::headerData ( int column ) const
    {
      if ( column < 0 || column >= _M_headers.size() ) return QVariant();
      return _M_headers.at ( column );
    }
    // ---------------------------------------------------------------------------------    
    bool SelectProjectsTableModelAdaptorPrivate::isCheckable(QModelIndex const& index) const
    {
      return index.column() == 0;
    }
    // ---------------------------------------------------------------------------------
    void SelectProjectsTableModelAdaptorPrivate::setCheckState(QModelIndex const& index, int check_state) 
    {
      Entry *e = _M_entries.at(index.row());
      e->check_state = check_state;
    }
    // ---------------------------------------------------------------------------------
    UuidList SelectProjectsTableModelAdaptorPrivate::selected() const
    {
      return UuidList();
    }
    // ---------------------------------------------------------------------------------
    void SelectProjectsTableModelAdaptorPrivate::setSelected ( UuidList const& )
    {
    }
    // ---------------------------------------------------------------------------------
    void SelectProjectsTableModelAdaptorPrivate::init_headers()
    {
      _M_headers << i18n ( "" ) << i18n ( "Name" );
    }
    // ---------------------------------------------------------------------------------
    void SelectProjectsTableModelAdaptorPrivate::init_projects_list()
    {
      ProjectList projects = context()->projectManager()->allProjects();
      foreach ( Project const& project, projects )
      {
        if ( project.isVisible() )
        {
          _M_entries <<  new Entry ( project );
        }
      }
    }
    // ---------------------------------------------------------------------------------
    //SelectProjectTableModelAdaptor:
    // ---------------------------------------------------------------------------------
    SelectProjectsTableModelAdaptor::SelectProjectsTableModelAdaptor ( QObject* parent )
        : SelectEntityTableModelAdaptor ( parent )
        , d_ptr ( new SelectProjectsTableModelAdaptorPrivate() )
    {}
    // ---------------------------------------------------------------------------------
    SelectProjectsTableModelAdaptor::~SelectProjectsTableModelAdaptor()
    {
      delete d_ptr;
    }
    // ---------------------------------------------------------------------------------
    QVariant SelectProjectsTableModelAdaptor::data ( const QModelIndex& index, int role ) const
    {
      const Q_D ( SelectProjectsTableModelAdaptor );
      return d->data ( index, role );
    }
    // ---------------------------------------------------------------------------------
    int SelectProjectsTableModelAdaptor::columnCount ( ) const
    {
      const Q_D ( SelectProjectsTableModelAdaptor );
      return d->columnCount();
    }
    // ---------------------------------------------------------------------------------
    int SelectProjectsTableModelAdaptor::rowCount ( ) const
    {
      const Q_D ( SelectProjectsTableModelAdaptor );
      return d->rowCount();
    }
    // ---------------------------------------------------------------------------------
    QVariant SelectProjectsTableModelAdaptor::headerData ( int column ) const
    {
      const Q_D ( SelectProjectsTableModelAdaptor );
      return d->headerData ( column );
    }
    // ---------------------------------------------------------------------------------
    bool SelectProjectsTableModelAdaptor::isCheckable(QModelIndex const& index) const
    {
      const Q_D ( SelectProjectsTableModelAdaptor );
      return d->isCheckable ( index );
    }
    // ---------------------------------------------------------------------------------
    void SelectProjectsTableModelAdaptor::setCheckState(QModelIndex const& index, int state)
    {
      Q_D ( SelectProjectsTableModelAdaptor );
      return d->setCheckState ( index, state);
    }
    // ---------------------------------------------------------------------------------
    UuidList SelectProjectsTableModelAdaptor::selected() const
    {
      const Q_D ( SelectProjectsTableModelAdaptor );
      return d->selected();
    }
    // ---------------------------------------------------------------------------------
    void SelectProjectsTableModelAdaptor::setSelected ( UuidList const& )
    {
    }
    // ---------------------------------------------------------------------------------
  }
}

