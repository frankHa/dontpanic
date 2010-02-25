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

#include "kactionstablesortmodel.h"
#include "kactionstablecolumns.h"
#include "kactionstablemodel.h"
namespace dp
{
// ---------------------------------------------------------------------------------
namespace core
{
// ---------------------------------------------------------------------------------
namespace detail
{
// ---------------------------------------------------------------------------------
KActionsTableSortModel::KActionsTableSortModel(QObject* parent)
        :QSortFilterProxyModel(parent)
{}
// ---------------------------------------------------------------------------------
bool KActionsTableSortModel::lessThan(QModelIndex const&left, QModelIndex const&right)const
{
    int column = left.column();
    if (column == START || column == END)
    {
        KActionsTableModel *source_model = static_cast<KActionsTableModel*>(sourceModel());
        Action const& l = source_model->at(left);
        Action const& r = source_model->at(right);
        switch (column)
        {
        case START:
            return l.startTime()<r.startTime();
        case END:
            return l.endTime()<r.endTime();
        }
    }
    return QSortFilterProxyModel::lessThan(left, right);
}
// ---------------------------------------------------------------------------------
}
// ---------------------------------------------------------------------------------
}
// ---------------------------------------------------------------------------------
}
// ---------------------------------------------------------------------------------
