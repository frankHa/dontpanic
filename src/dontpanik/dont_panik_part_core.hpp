#ifndef DP_CORE_HPP
#define DP_CORE_HPP
//dp includes
#include "defines.hpp"
//Qt includes
#include <QObject>
// ---------------------------------------------------------------------------------
//forward decl:
class QTextEdit;
class KXMLGUIClient;
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
        dont_panik_core ( KXMLGUIClient *gui_client, QWidget *parent );
        // ---------------------------------------------------------------------------------
      public:
        // ---------------------------------------------------------------------------------
        void editProjects();
        // ---------------------------------------------------------------------------------
        void editWorkTypes();
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
        KXMLGUIClient * _M_gui_client;
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
