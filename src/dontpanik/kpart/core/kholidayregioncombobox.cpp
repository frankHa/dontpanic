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

#include "kholidayregioncombobox.h"
#include <KHolidays/Holidays>
#include <KStandardDirs>
#include <KConfig>
#include <KConfigGroup>
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  namespace core
  {
    // ---------------------------------------------------------------------------------
    KHolidayRegionComboBox::KHolidayRegionComboBox ( QWidget* parent )
        : QComboBox ( parent )
    {
      init();
    }
    // ---------------------------------------------------------------------------------
    void KHolidayRegionComboBox::init()
    {
      QString currentHolidayName;
      QStringList holidayList;
      QStringList countryList = KHolidays::HolidayRegion::locations();

      foreach ( const QString &country, countryList )
      {
        QString countryFile = KStandardDirs::locate ( "locale",
                              "l10n/" + country + "/entry.desktop" );
        QString regionName;
        if ( !countryFile.isEmpty() )
        {
          KConfig _cfg ( countryFile, KConfig::SimpleConfig );
          KConfigGroup cfg ( &_cfg, "KCM Locale" );
          regionName = cfg.readEntry ( "Name" );
        }
        if ( regionName.isEmpty() )
        {
          regionName = country;
        }

        holidayList << regionName;
        //mRegionMap[regionName] = country; //store region for saving to config file

//         if ( KOGlobals::self()->holidays() &&
//              ( country == KOGlobals::self()->holidays()->location() ) )
//         {
//           currentHolidayName = regionName;
//         }
      }
      holidayList.sort();
      holidayList.push_front (
        i18nc ( "@item:inlistbox do not use holidays", "(None)" ) );

      addItems ( holidayList );
    }
    // ---------------------------------------------------------------------------------
  }
  // ---------------------------------------------------------------------------------
}
// ---------------------------------------------------------------------------------

