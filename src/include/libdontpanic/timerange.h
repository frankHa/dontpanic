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

#ifndef DP_TIMERANGE_H
#define DP_TIMERANGE_H
#include <libdontpanic/defines.hpp>
#include <QDateTime>
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  class TimeRange
  {
    // ---------------------------------------------------------------------------------
    public:
      // ---------------------------------------------------------------------------------
      TimeRange();
      // ---------------------------------------------------------------------------------
      TimeRange(QDateTime const& from, QDateTime const& to);
      // ---------------------------------------------------------------------------------
    public:
      // ---------------------------------------------------------------------------------
      TimeRange &setFrom(QDateTime const& from);
      // ---------------------------------------------------------------------------------
      QDateTime from() const;
      // ---------------------------------------------------------------------------------
      TimeRange& setTo(QDateTime const& to);
      // ---------------------------------------------------------------------------------
      QDateTime to() const;
      // ---------------------------------------------------------------------------------
      int duration() const;
      // ---------------------------------------------------------------------------------      
      bool isValid() const;
      // ---------------------------------------------------------------------------------      
    private:
      // ---------------------------------------------------------------------------------
      QDateTime _M_from;
      // ---------------------------------------------------------------------------------
      QDateTime _M_to;
      // ---------------------------------------------------------------------------------
    };
    // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
#endif // DP_TIMERANGE_H
