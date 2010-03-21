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

#include <libdontpanic/reporttype.h>
// ---------------------------------------------------------------------------------
namespace dp
{
  ///ctor
  ReportType::ReportType()
      : _M_id ( Uuid::generate() )
      , _M_title ( "" ) {}
  // ---------------------------------------------------------------------------------
  ReportType::ReportType ( QString const& title )
      : _M_id ( Uuid::generate() )
      , _M_title ( title ) {}
  // ---------------------------------------------------------------------------------
  ReportType::ReportType ( Uuid const& id )
      : _M_id ( id )
      , _M_title ( "" ) {}
  // ---------------------------------------------------------------------------------
  Uuid const& ReportType::id() const
  {
    return _M_id;
  }
  // ---------------------------------------------------------------------------------
  QString ReportType::title() const
  {
    return _M_title;
  }
  // ---------------------------------------------------------------------------------
  ReportType& ReportType::setTitle ( QString title )
  {
    _M_title = title;
    return *this;
  }
  // ---------------------------------------------------------------------------------
  bool DP_EXPORT operator == (dp::ReportType const& lhs, dp::ReportType const& rhs)
  {
    return lhs.id() == rhs.id();
  }
  // ---------------------------------------------------------------------------------
}
// ---------------------------------------------------------------------------------
