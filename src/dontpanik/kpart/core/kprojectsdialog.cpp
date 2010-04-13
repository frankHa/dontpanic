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

#include "kprojectsdialog.h"
#include "keditprojectdialog.h"
#include "ui_kprojectsdialog.h"
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  namespace core
  {
    // ---------------------------------------------------------------------------------
    KProjectsDialog::KProjectsDialog ( QWidget *parent )
        : KDialog ( parent )
        , _M_ui ( new Ui::KProjectsDialog () )
    {
      QWidget *w= new QWidget(this);
      _M_ui->setupUi ( w );
      setMainWidget(w);
      setButtons(Ok|Cancel);
      setCaption(i18n("Projects"));
      setInitialSize(QSize(470, 460));
      setup_actions();
    }
    // ---------------------------------------------------------------------------------
    KProjectsDialog::~KProjectsDialog ()
    {
      delete _M_ui;
    }
    // ---------------------------------------------------------------------------------
    // private stuff:
    // ---------------------------------------------------------------------------------
    void KProjectsDialog::setup_actions()
    {
      connect(_M_ui->b_add, SIGNAL(clicked()), this, SLOT(add()));
      connect(_M_ui->b_remove, SIGNAL(clicked()), _M_ui->tableView, SLOT(on_remove_selected_project()));
    }
    // ---------------------------------------------------------------------------------
    void KProjectsDialog::add()
    {
      KEditProjectDialog dlg(this);
      dlg.exec();
    }
    // ---------------------------------------------------------------------------------
  }//core
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
