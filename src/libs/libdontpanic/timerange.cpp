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

#include <libdontpanic/timerange.h>

namespace dp
{
  // ---------------------------------------------------------------------------------
  TimeRange::TimeRange()
  :_M_from()
  ,_M_to(){}
  // ---------------------------------------------------------------------------------
  TimeRange::TimeRange(QDateTime const& from, QDateTime const& to)
  :_M_from(from)
  ,_M_to(to)
  {}
  // ---------------------------------------------------------------------------------
  TimeRange & TimeRange::setFrom(QDateTime const& from)
  {
    _M_from = from;
    return *this;
  }
  // ---------------------------------------------------------------------------------
  QDateTime TimeRange::from() const
  {
    return _M_from;
  }
  // ---------------------------------------------------------------------------------
  TimeRange& TimeRange::setTo(QDateTime const& to)
  {
    _M_to = to;
    return *this;
  }
  // ---------------------------------------------------------------------------------
  QDateTime TimeRange::to() const
  {
    return _M_to;
  }
  // ---------------------------------------------------------------------------------
  int TimeRange::duration() const
  {
    QDateTime start = from();
    if(start.isNull()){return 0;}    
    QDateTime end;
    if(to().isNull())
    {
      end = QDateTime::currentDateTime();
    } else
    {
      end = to();
    }
    return (start.secsTo(end));    
  }
  // ---------------------------------------------------------------------------------      
}

