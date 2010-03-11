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

#include "country.h"

#include <KStandardDirs>
#include <KConfig>
#include <KConfigGroup>

namespace dp
{

  namespace core
  {
    Country::Country( QString const& c )
        : _M_country ( c )
    {
      QString countryFile = KStandardDirs::locate ( "locale",
                            "l10n/" + c + "/entry.desktop" );
      QString regionName;
      if ( !countryFile.isEmpty() )
      {
        KConfig _cfg ( countryFile, KConfig::SimpleConfig );
        KConfigGroup cfg ( &_cfg, "KCM Locale" );
        _M_display_name = cfg.readEntry ( "Name" );
      }
      if ( _M_display_name.isEmpty() )
      {
        _M_display_name = c;
      }      
    }
    
    QString Country::displayName() const
    {
      return _M_display_name;
    }

    Country country ( QString const& c )
    {
      return Country ( c );
    }
  }

}

