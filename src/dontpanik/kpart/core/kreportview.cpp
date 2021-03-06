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

#include "kreportview.h"
#include "ui_kreportview.h"
#include "context.h"

namespace dp
{
  namespace core
  {
    KReportView::KReportView(QWidget *parent)
    :QWidget(parent)
    ,_M_ui(new Ui::KReportView())
    {
      _M_ui->setupUi(this);
      _M_ui->splitter->setSizes ( QList<int>() << 150 << 500 );
      
    }
    
    KReportView::~KReportView(){delete _M_ui;}
    
  }
}

