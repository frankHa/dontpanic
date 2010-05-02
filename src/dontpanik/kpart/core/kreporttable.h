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

#ifndef DP_CORE_KREPORTTABLE_H
#define DP_CORE_KREPORTTABLE_H

#include <QTableView>

class QSortFilterProxyModel;
class QContextMenuEvent;
class QFileInfo;
class KAction;
namespace dp
{
  // ---------------------------------------------------------------------------------
  class Report;
  // ---------------------------------------------------------------------------------
  namespace core
  {
    // ---------------------------------------------------------------------------------
    class KReportTableModel;
    // ---------------------------------------------------------------------------------
    class KReportTable : public QTableView
    {
        // ---------------------------------------------------------------------------------
        Q_OBJECT
        // ---------------------------------------------------------------------------------
      public:
        // ---------------------------------------------------------------------------------
        KReportTable ( QWidget* parent = 0 );
        // ---------------------------------------------------------------------------------
        void setReport ( Report const& data );
        // ---------------------------------------------------------------------------------
        void resetReport ();
        // ---------------------------------------------------------------------------------
      protected slots:
        // ---------------------------------------------------------------------------------
        virtual void contextMenuEvent(QContextMenuEvent* evt);
        // ---------------------------------------------------------------------------------
      private:
        // ---------------------------------------------------------------------------------
        void init();
        // ---------------------------------------------------------------------------------
        void setup_actions();
        // ---------------------------------------------------------------------------------
      private slots:
        // ---------------------------------------------------------------------------------
        void export_data_to_file();
        // ---------------------------------------------------------------------------------
      private:
        // ---------------------------------------------------------------------------------
        KReportTableModel *_M_data_model;
        // ---------------------------------------------------------------------------------
        QSortFilterProxyModel *_M_sort_model;
        // ---------------------------------------------------------------------------------
        KAction *_M_export_data_action;
        // ---------------------------------------------------------------------------------        
    };
    // ---------------------------------------------------------------------------------
  }
  // ---------------------------------------------------------------------------------
}
// ---------------------------------------------------------------------------------
#endif // DP_CORE_KREPORTTABLE_H
