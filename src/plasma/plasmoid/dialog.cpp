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

#include "dialog.h"
#include "plasma-dontpanic.h"

#include <QGraphicsLinearLayout>

//Plasma includes
#include <Plasma/Label>

namespace dp
{
 namespace plasma
 {
  namespace applet
  {
    Dialog::Dialog(PlasmaDontPanic *dp, QObject *parent)
    :QObject(parent)
    , _M_label(0)
    , _M_widget(0)
    {
      _M_widget = new QGraphicsWidget(dp);
      QGraphicsLinearLayout *layout = new QGraphicsLinearLayout(_M_widget);
      _M_label = new Plasma::Label(_M_widget);
      _M_label->setText("Don't Panic");
      layout->addItem(_M_label);
    }
    
    QGraphicsWidget* Dialog::dialog()
    {
      return _M_widget;
    }
  }
 }
}

