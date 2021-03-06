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

#ifndef DP_REPORTDATAFILTER_H
#define DP_REPORTDATAFILTER_H
#include <libdontpanic/defines.hpp>
#include <libdontpanic/uuid.h>
// ---------------------------------------------------------------------------------
namespace dp
{
  class ReportDataFilter;
}
// ---------------------------------------------------------------------------------
Q_DECLARE_METATYPE ( dp::ReportDataFilter )
// ---------------------------------------------------------------------------------

namespace dp
{
  // ---------------------------------------------------------------------------------
  class DP_EXPORT ReportDataFilter
  {
      // ---------------------------------------------------------------------------------
    public:
      // ---------------------------------------------------------------------------------
      ReportDataFilter();
      // ---------------------------------------------------------------------------------
    public:
      // ---------------------------------------------------------------------------------
      int filterType() const;
      // ---------------------------------------------------------------------------------
      ReportDataFilter& setFilterType ( int type );
      // ---------------------------------------------------------------------------------
      ReportDataFilter& setSelection ( UuidList const& ids );
      // ---------------------------------------------------------------------------------
      UuidList &selection();
      // ---------------------------------------------------------------------------------
      UuidList const& selection() const;
      // ---------------------------------------------------------------------------------
    private:
      // ---------------------------------------------------------------------------------
      int _M_type;
      // ---------------------------------------------------------------------------------
      UuidList _M_selection;
      // ---------------------------------------------------------------------------------
  };
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
#endif // DP_REPORTDATAFILTER_H
