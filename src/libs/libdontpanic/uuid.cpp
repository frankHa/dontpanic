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

#include "uuid.h"
#include <libdontpanic/config.h>
#ifdef HAVE_LIBUUID
#include <uuid/uuid.h>
#endif //HAVE_LIBUUID

namespace dp
{
  QUuid Uuid::generate()
  {
    #ifdef HAVE_LIBUUID
     uuid_t id;
     char id_string[37];
     uuid_generate(id);
     uuid_unparse(id, id_string);
     return QUuid(id_string);
     
    #else
      return QUuid::createUuid();
    #endif //HAVE_LIBUUID
  }
}

