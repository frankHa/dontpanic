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

#include "context.h"

namespace dp
{
  namespace core
  {
    Context _instance;

    Context* context()
    {
      return &_instance;
    }

    Context::Context()
    :_M_project_manager(new dp::client::ProjectManager())
    {
      qDebug()<<__FUNCTION__;
    }
    
    Context::~Context()
    {
      delete _M_project_manager;
    }

    dp::client::ProjectManager* Context::projectManager()
    {
      return _M_project_manager;
    }
  }
}
