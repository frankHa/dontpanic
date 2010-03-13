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
#include <libdontpanic/durationformatter.h>
#include "context.h"
#include <KStatusBar>
#include <QToolTip>

namespace dp
{
  namespace core
  {
    // ---------------------------------------------------------------------------------
    KDurationStatusUpdater::KDurationStatusUpdater ( QObject* parent)
    :QObject(parent)
    , _M_status_bar(0)
    , _M_duration_label(0)
    {
    }
    // ---------------------------------------------------------------------------------
    void KDurationStatusUpdater::addTo(KParts::StatusBarExtension* sb)
    {
      _M_status_bar = sb;
    }
    // ---------------------------------------------------------------------------------
    void KDurationStatusUpdater::onCurrentlySelectedDaysDurationChanged ( int duration )
    {
      if(statusBar()->statusBar()== 0){return;}
      if(label() == 0) {initLabel();}
      label()->setText(duration_formatter().format(duration));  
    }
    // ---------------------------------------------------------------------------------
    void KDurationStatusUpdater::onCurrentProjectChanged ( QString const& project_description )
    {
      if(statusBar()->statusBar()== 0){return;}
      if(label() == 0) {initLabel();}
      label()->setToolTip(project_description);      
    }
    // ---------------------------------------------------------------------------------
    void KDurationStatusUpdater::initLabel()
    {
      _M_duration_label = new QLabel();
      QFont font;
      font.setBold(true);
      _M_duration_label->setFont(font);
      _M_duration_label->setAlignment(Qt::AlignRight);
      _M_duration_label->setIndent(10);
      statusBar()->statusBar()->addPermanentWidget(label(),0);
    }
    // ---------------------------------------------------------------------------------
    KParts::StatusBarExtension * KDurationStatusUpdater::statusBar()
    {
      return _M_status_bar;
    }
    // ---------------------------------------------------------------------------------
    QLabel* KDurationStatusUpdater::label()
    {
      return _M_duration_label;
    }
    // ---------------------------------------------------------------------------------
  }
  // ---------------------------------------------------------------------------------
}
// ---------------------------------------------------------------------------------