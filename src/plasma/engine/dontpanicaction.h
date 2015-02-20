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

#ifndef DP_PLASMA_DONTPANICACTION_H
#define DP_PLASMA_DONTPANICACTION_H
#include <Plasma/ServiceJob>
// ---------------------------------------------------------------------------------
namespace dp
{
  namespace plasma
  {

    class DontPanicAction : public Plasma::ServiceJob
    {
      // ---------------------------------------------------------------------------------
      Q_OBJECT
      // ---------------------------------------------------------------------------------
      public:
      // ---------------------------------------------------------------------------------
      DontPanicAction ( const QString& destination,
                        const QString& operation,
                        QMap<QString,QVariant>& parameters,
                        QObject* parent = 0 )
          : ServiceJob ( destination, operation, parameters, parent ) {}
      // ---------------------------------------------------------------------------------
      void start();
      // ---------------------------------------------------------------------------------
    private:
      // ---------------------------------------------------------------------------------
      void stopCurrentAction();
      // ---------------------------------------------------------------------------------
      void startFromFavorite();
      // ---------------------------------------------------------------------------------
      void continueLastAction();
      // ---------------------------------------------------------------------------------
    };
  }
}

#endif // DP_PLASMA_DONTPANICACTION_H
