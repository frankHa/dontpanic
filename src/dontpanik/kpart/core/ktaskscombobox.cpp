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

#include "ktaskscombobox.h"
#include "context.h"
#include <QVariant>
namespace dp
{
 namespace core
 {
   namespace detail
   {
     // ---------------------------------------------------------------------------------
     KTasksComboBox::KTasksComboBox(QWidget *parent)
     :QComboBox(parent)
     {
       init();
     }
     // ---------------------------------------------------------------------------------
     void KTasksComboBox::select(QUuid const& id)
     {
       int index = findData(QVariant(id.toString()));
       setCurrentIndex(index);
     }
     // ---------------------------------------------------------------------------------
     QUuid KTasksComboBox::selectedUuid() const
     {
       return QUuid(itemData(currentIndex()).toString());
     }     
     // ---------------------------------------------------------------------------------
     // private stuff:
     // ---------------------------------------------------------------------------------
     void KTasksComboBox::init()
     {
       TaskList tasks = context()->taskManager()->allTasks();
       TaskList::const_iterator it;
       for(it=tasks.begin();it!=tasks.end();++it)
       {
         addItem(it->name(), QVariant(it->id().toString()));
       }
     }
     // ---------------------------------------------------------------------------------
   }
 }
}

