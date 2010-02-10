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

#ifndef DP_CORE_DAYINFO_H
#define DP_CORE_DAYINFO_H
#include <libdontpanic/defines.hpp>
#include <QDate>

namespace dp
{
  namespace core
  {
    class DayInfo
    {
      public:
      DayInfo(QDate const& date, int wt=0);
      public:
      DayInfo setDate(QDate const& date);
      QDate date() const;
      
      DayInfo workTime(int d);
      int workTime()const; 
      
      private:
        QDate _M_date;
        int _M_worktime;
    };
  }
}

#endif // DP_CORE_DAY_H
