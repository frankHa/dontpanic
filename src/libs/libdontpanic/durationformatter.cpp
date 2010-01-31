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

#include <libdontpanic/durationformatter.h>

namespace dp
{
  // ---------------------------------------------------------------------------------
  QString DurationFormatter::format(int duration)
  {
    int mins = duration%60;
    int h = (duration-mins)/60;
    QString result = QString("%L1:%L2").arg(h,2, 10, QChar('0')).arg(mins,2, 10, QChar('0'));
    return result;
  }
  // ---------------------------------------------------------------------------------
}

