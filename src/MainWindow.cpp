/****************************************************************************
 **
 ** Copyright (C) 2011-2017 Philippe Steinmann.
 **
 ** This file is part of Mdt Application Example .
 **
 ** Mdt is free software: you can redistribute it and/or modify
 ** it under the terms of the GNU Lesser General Public License as published by
 ** the Free Software Foundation, either version 3 of the License, or
 ** (at your option) any later version.
 **
 ** Mdt is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU Lesser General Public License for more details.
 **
 ** You should have received a copy of the GNU Lesser General Public License
 ** along with Mdt.  If not, see <http://www.gnu.org/licenses/>.
 **
 ****************************************************************************/
#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <Mdt/ItemModel/VariantTableModel.h>

using namespace Mdt::ItemModel;

MainWindow::MainWindow(QWidget* parent)
 : QMainWindow(parent),
   mUi( std::make_unique<Ui::MainWindow>() )
{
  mUi->setupUi(this);

  auto *model = new VariantTableModel(VariantTableModelStorageRule::GroupDisplayAndEditRoleData, this);
  mUi->tableView->setModel(model);
  model->populate(5, 3);
}

MainWindow::~MainWindow()
{
}
