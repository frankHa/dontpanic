#include "selectentitytablemodeladaptor.h"
#include "selectentitytablemodeladaptor.moc"
#include "context.h"
#include <libdontpanic/project.hpp>
#include <libdontpanic/task.hpp>

#include <QVariant>
#include <QModelIndex>
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  namespace core
  {
    // ---------------------------------------------------------------------------------
    
    // ---------------------------------------------------------------------------------
    SelectEntityTableModelAdaptor::SelectEntityTableModelAdaptor ( QObject* parent )
    :QObject(parent){}
    // ---------------------------------------------------------------------------------
    SelectEntityTableModelAdaptor::~SelectEntityTableModelAdaptor(){qDeleteAll( _M_data);}
    // ---------------------------------------------------------------------------------
    QVariant SelectEntityTableModelAdaptor::data ( const QModelIndex& index ) const
    {
      Entry const*e = _M_data.value(index.row());
      if(index.column() == 1)
      {
        return e->name();
      }
      return QVariant();
    }
    // ---------------------------------------------------------------------------------
    int SelectEntityTableModelAdaptor::columnCount ( ) const
    {
      return _M_headers.count();
    }
    // ---------------------------------------------------------------------------------
    int SelectEntityTableModelAdaptor::rowCount ( ) const
    {
      return _M_data.count();
    }
    // ---------------------------------------------------------------------------------
    QVariant SelectEntityTableModelAdaptor::headerData ( int column ) const
    {
      return _M_headers.value(column);
    }
    // ---------------------------------------------------------------------------------
    bool SelectEntityTableModelAdaptor::isCheckable ( int column ) const
    {
      return (column == 0);
    }
    // ---------------------------------------------------------------------------------
    int SelectEntityTableModelAdaptor::checkState ( int row ) const
    {
      return _M_data.value(row)->check_state();
    }
    // ---------------------------------------------------------------------------------
    void SelectEntityTableModelAdaptor::setCheckState ( int row, int state )
    {
      _M_data.value(row)->set_check_state(state);
    }
    // ---------------------------------------------------------------------------------
    UuidList SelectEntityTableModelAdaptor::selected() const
    {
      return UuidList();
    }
    // ---------------------------------------------------------------------------------
    void SelectEntityTableModelAdaptor::setSelected ( UuidList const& )
    {
    }
    // ---------------------------------------------------------------------------------
    void SelectEntityTableModelAdaptor::add ( SelectEntityTableModelAdaptor::Entry* entry )
    {
      _M_data<<entry;
    }
    // ---------------------------------------------------------------------------------
    void SelectEntityTableModelAdaptor::addColumn ( const QString& header )
    {
      _M_headers<<header;
    }
    // ---------------------------------------------------------------------------------
    //SelectProjectsTableModelAdaptor:
    // ---------------------------------------------------------------------------------
    SelectProjectsTableModelAdaptor::SelectProjectsTableModelAdaptor(QObject *parent)
     :SelectEntityTableModelAdaptor(parent)
    {
      init_headers();
      init_data();
    }
    // ---------------------------------------------------------------------------------
    void SelectProjectsTableModelAdaptor::init_headers()
    {
      addColumn("");
      addColumn(i18n("Name"));
    }
    // ---------------------------------------------------------------------------------
    void SelectProjectsTableModelAdaptor::init_data()
    {
      class ProjectEntry : public SelectEntityTableModelAdaptor::Entry
      {
        public:
          ProjectEntry(Project const&p):_M_p(p){}
        public:
          QString name() const {return _M_p.name();}
          Uuid const& id() const {return _M_p.id();}
          
        private:
          Project _M_p;
      };
      ProjectList const& projects = context()->projectManager()->allProjects();
      foreach(Project const& p, projects)
      {
        if(p.isVisible())
        {
          add(new ProjectEntry(p));
        }
      }      
    }
    // ---------------------------------------------------------------------------------
    // ---------------------------------------------------------------------------------
    //SelectTasksTableModelAdaptor:
    // ---------------------------------------------------------------------------------
    SelectTasksTableModelAdaptor::SelectTasksTableModelAdaptor(QObject *parent)
    :SelectEntityTableModelAdaptor(parent)
    {
      init_headers();
      init_data();
    }
    // ---------------------------------------------------------------------------------
    void SelectTasksTableModelAdaptor::init_headers()
    {
      addColumn("");
      addColumn(i18n("Name"));
    }
    // ---------------------------------------------------------------------------------
    void SelectTasksTableModelAdaptor::init_data()
    {
      class TaskEntry : public SelectEntityTableModelAdaptor::Entry
      {
        public:
          TaskEntry(Task const&p):_M_p(p){}
        public:
          QString name() const {return _M_p.name();}
          Uuid const& id() const {return _M_p.id();}
          
        private:
          Task _M_p;
      };
      TaskList const& projects = context()->taskManager()->allTasks();
      foreach(Task const& p, projects)
      {
        if(p.isVisible())
        {
          add(new TaskEntry(p));
        }
      }      
    }
    // ---------------------------------------------------------------------------------
  }
  // ---------------------------------------------------------------------------------
}
