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

#include "keditactiondialog.h"
#include "ui_keditactiondialog.h"
#include "context.h"
#include <libdontpanic/action.hpp>
namespace dp
{ 
  namespace core
  {
    KEditActionDialog::KEditActionDialog ( QWidget* parent, Qt::WindowFlags f)
    : QDialog(parent, f)
    , _M_ui(new Ui::KEditActionDialog())
    {
      _M_ui->setupUi(this);
      init_ui();
      setup_actions();
    }
    
    KEditActionDialog::~KEditActionDialog()
    {
      delete _M_ui;
    }
    
    KEditActionDialog& KEditActionDialog::setCurrentDay(QDate const& date)
    {
      _M_ui->dateEdit->setDate(date);
    }
    
    KEditActionDialog& KEditActionDialog::setAction(Action const& a)
    {
      _M_current_action = a;
      setCurrentDay(a.startTime().date());
      _M_ui->starting->setTime(a.startTime().time());
      _M_ui->ending->setTime(a.endTime().time());
      _M_ui->next_day->setChecked(a.startTime().date().day()<a.endTime().date().day());
      _M_ui->title->setText(a.name());
      _M_ui->projects->select(a.project());
      _M_ui->worktype->select(a.task());
      _M_ui->comment->setText(a.comment());
    }
    
    void KEditActionDialog::init_ui()
    {
      _M_ui->starting->setTime(QTime::currentTime());
      _M_ui->ending->setTime(QTime::currentTime());
    }
    
    void KEditActionDialog::setup_actions()
    {
      connect(_M_ui->buttonBox, SIGNAL(accepted()), this, SLOT(accepted()));
    }
    
    QDate KEditActionDialog::currentDate() const
    {
      return _M_ui->dateEdit->date();
    }
    
    void KEditActionDialog::accepted()
    {
      Action a;
      if(_M_current_action.isValid())
      {
        a = _M_current_action;
      }
      a.setStartTime(QDateTime(currentDate(), _M_ui->starting->time()));
      QDate endDate = currentDate();
      if(_M_ui->next_day->isChecked())
      {
       endDate = endDate.addDays(1); 
      }
      a.setEndTime(QDateTime(endDate, _M_ui->ending->time()));
      a.setName(_M_ui->title->text());
      a.setProject(_M_ui->projects->selectedUuid());
      a.setTask(_M_ui->worktype->selectedUuid());
      a.setComment(_M_ui->comment->text());
      context()->timeTracker()->store(a);
    }
  }
}

