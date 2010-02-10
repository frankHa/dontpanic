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

#include "kdurationstatusupdater.h"

namespace dp
{
  namespace core
  {
    KDurationStatusUpdater::KDurationStatusUpdater ( QObject* parent)
    :QObject(parent)
    , _M_status_bar(0)
    , _M_duration_label(0)
    , _M_timer(new QTimer(this))
    {
    }
    void KDurationStatusUpdater::addTo(KParts::StatusBarExtension* sb)
    {
      _M_status_bar = sb;
      connect(timer(), SIGNAL(timeout()), this, SLOT(update()));
      timer()->start(1000);
    }
    
    void KDurationStatusUpdater::update()
    {
      if(statusBar()->statusBar()== 0){return;}
      if(label() == 0) {initLabel();}
      label()->setText("hallo");
    }
    
    void KDurationStatusUpdater::initLabel()
    {
      _M_duration_label = new QLabel();
      QFont font;
      font.setBold(true);
      _M_duration_label->setFont(font);
      statusBar()->addStatusBarItem(label(),0 ,true);
    }
    
    KParts::StatusBarExtension * KDurationStatusUpdater::statusBar()
    {
      return _M_status_bar;
    }
    
    QLabel* KDurationStatusUpdater::label()
    {
      return _M_duration_label;
    }
    QTimer* KDurationStatusUpdater::timer()
    {
      return _M_timer;
    }
  }
}