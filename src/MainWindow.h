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
#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <memory>

namespace Ui{
  class MainWindow;
}

/*! \brief Main window of the application
 */
class MainWindow : public QMainWindow
{
 Q_OBJECT

 public:

  /*! \brief Constructor
   */
  explicit MainWindow(QWidget *parent = nullptr);

  // unique_ptr needs the complete definition of Ui::MainWindow
  ~MainWindow();

 private:

  std::unique_ptr<Ui::MainWindow> mUi;
};

#endif // #ifndef MAIN_WINDOW_H
