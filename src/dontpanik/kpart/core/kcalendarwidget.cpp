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

#include "kcalendarwidget.h"
#include <QPainter>
#include "context.h"

namespace dp
 {
   namespace core
   {

    KCalendarWidget::KCalendarWidget ( QWidget* parent )
    :QCalendarWidget(parent){}
    
    void KCalendarWidget::paintCell ( QPainter* painter, const QRect& rect, const QDate& date ) const
    {
      if(!date.isValid() || date == selectedDate())
      {
        QCalendarWidget::paintCell(painter, rect, date);
        return;
      }
      QFont font = painter->font();
      font.setBold(haveActionsFor(date));
      painter->setFont(font);
      painter->setPen(color_for(date));
      painter->drawText(rect, QString::number(date.day()), QTextOption(Qt::AlignHCenter));      
    }

    QColor KCalendarWidget::color_for(QDate const& date) const
    {
      if(!belongsToThisMonth(date))
      {
        return Qt::gray;
      }
      if(isHoliday(date))
      {
        return Qt::red;
      }
      return Qt::black;
    }
    
    bool KCalendarWidget::isHoliday(QDate const& date) const
    {
      return (date.dayOfWeek()==Qt::Saturday || date.dayOfWeek() == Qt::Sunday
              || !context()->plannedWorkingtimeManager()->isWorkDay(date));
    }
    
    bool KCalendarWidget::haveActionsFor(QDate const& date) const
    {
      return context()->timeTracker()->hasActionsFor(date);
    }
    
    bool KCalendarWidget::belongsToThisMonth(QDate const& date) const
    {
      return date.month() == this->monthShown();
    }
    
   }
 }