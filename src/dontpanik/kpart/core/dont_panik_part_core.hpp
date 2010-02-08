#ifndef DP_CORE_HPP
#define DP_CORE_HPP
//dp includes
#include "libdontpanic/defines.hpp"
//Qt includes
#include <QObject>
#include <kparts/part.h>
// ---------------------------------------------------------------------------------
//forward decl:
class QTextEdit;
class KAction;
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  namespace core
  {
    // ---------------------------------------------------------------------------------
    class KMainWidget;
    // ---------------------------------------------------------------------------------
    class DP_EXPORT dont_panik_core
          : public QObject
    {
        // ---------------------------------------------------------------------------------
        Q_OBJECT
        // ---------------------------------------------------------------------------------
      public:
        // ---------------------------------------------------------------------------------
        dont_panik_core ( KParts::ReadOnlyPart *gui_client, QWidget *parent );
        // ---------------------------------------------------------------------------------
      public slots:
        // ---------------------------------------------------------------------------------
        void editProjects();
        // ---------------------------------------------------------------------------------
        void editTasks();
        // ---------------------------------------------------------------------------------
        void addAction();
        // ---------------------------------------------------------------------------------
        void stopCurrentAction();
        // ---------------------------------------------------------------------------------
        void continueLastAction();
        // ---------------------------------------------------------------------------------
        void startNewAction();
        // ---------------------------------------------------------------------------------
        void viewDayAction();
        // ---------------------------------------------------------------------------------
        void viewReportsAction();
        // ---------------------------------------------------------------------------------
      public:
        // ---------------------------------------------------------------------------------
        /**
        * This must be implemented by each part
        */
        virtual bool openFile();
        // ---------------------------------------------------------------------------------
        virtual bool is_read_write() const;
        // ---------------------------------------------------------------------------------
        virtual QWidget* widget();
        // ---------------------------------------------------------------------------------
      private:
        // ---------------------------------------------------------------------------------
        bool _M_read_write;
        // ---------------------------------------------------------------------------------
        KParts::ReadOnlyPart * _M_gui_client;
        // ---------------------------------------------------------------------------------
        KMainWidget *_M_widget;
        // ---------------------------------------------------------------------------------

    };
    // ---------------------------------------------------------------------------------
  }//core
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
#endif//DP_CORE_HPP
