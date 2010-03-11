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
#include "country.h"
#include <KHolidays/Holidays>
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
      //QStringList holidayList;
      QStringList countryList = KHolidays::HolidayRegion::locations();
      QMap<QString, QString> holidayRegions;

      foreach ( const QString &country, countryList )
      {
        QString regionName = dp::core::country(country).displayName();

        holidayRegions[regionName] = country;
      }
      QStringList displayStrings = holidayRegions.keys();
      displayStrings.sort();
      //displayStrings.push_front (
      //  i18nc ( "@item:inlistbox do not use holidays", "(None)" ) );

      addItem ( i18nc ( "@item:inlistbox do not use holidays", "(None)" ), "" );
      foreach ( QString const& displayString, displayStrings )
      {
        addItem ( displayString, holidayRegions.value ( displayString ) );
      }
    }
    // ---------------------------------------------------------------------------------
    void KHolidayRegionComboBox::selectRegion ( QString const& region )
    {
      int index = findData ( QVariant ( region ) );
      setCurrentIndex ( index );
    }
    // ---------------------------------------------------------------------------------
    QString KHolidayRegionComboBox::selectedRegion() const
    {
      return itemData ( currentIndex() ).toString();
    }
    // ---------------------------------------------------------------------------------
  }
  // ---------------------------------------------------------------------------------
}
// ---------------------------------------------------------------------------------

