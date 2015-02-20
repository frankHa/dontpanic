/*
 * <one line to give the library's name and an idea of what it does.>
 * Copyright (C) 2014  Frank Habel <frank@bugplasma.de>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "dontpanicaction.h"
#include <libdontpanic_client/timetracker.h>
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  namespace plasma
  {
    // ---------------------------------------------------------------------------------
    void DontPanicAction::start()
    {
      qDebug()<<"starting DontPanicAction: "<<operationName();
      if(operationName()=="stopCurrentAction")
      {
        stopCurrentAction();
      }
      else if (operationName() == "continueLastAction")
      {
        continueLastAction();
      }
      else if(operationName()=="startFromFavorite")
      {
        startFromFavorite();
      }
    }
    // ---------------------------------------------------------------------------------
    void DontPanicAction::stopCurrentAction()
    {
      dp::client::TimeTracker tt;
      tt.stopCurrentAction();
    }
    // ---------------------------------------------------------------------------------
    void DontPanicAction::continueLastAction()
    {
      dp::client::TimeTracker tt;
      tt.continueLastAction();
    }
    // ---------------------------------------------------------------------------------
    void DontPanicAction::startFromFavorite()
    {
      dp::Uuid const& id = parameters()["favId"].toString();
      dp::client::TimeTracker tt;
      tt.startActionFromTemplate(id);
    }
    // ---------------------------------------------------------------------------------
  }
  // ---------------------------------------------------------------------------------
}
// ---------------------------------------------------------------------------------
#include "dontpanicaction.moc"
