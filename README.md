Linux: [![Build Status](https://travis-ci.org/scandyna/mdt-app-example.svg?branch=master)](https://travis-ci.org/scandyna/mdt-app-example)
Windows: [![Build Status](https://ci.appveyor.com/api/projects/status/gltn853s147blxlq?svg=true)](https://ci.appveyor.com/project/scandyna/mdt-app-example)

# A minimal Mdt based application

This is a example application made to explain
how to use the [Mdt](https://github.com/scandyna/multidiagtools) library .

It is also used to check distributed releases of Mdt.

## Install Mdt

Before we are able to build the application,
we have to install Mdt.

See the [INSTALL](https://github.com/scandyna/multidiagtools/blob/master/INSTALL.md) file from Mdt for how to proceed.

## Build the application on Linux

Create a build directory and go to it:
```bash
mkdir -p build/release
cd build/release
```

If Mdt was installed in system standard way (for example using Debian packages),
and it uses system wide installed Qt5, following should be enouth:
```bash
cmake ../../
```

To use a non system wide installed Qt5 and Mdt, cmake must know it:
```bash
cmake -D MDT_PREFIX_PATH=~/opt/mdt/release ../../
```

It is also possible to specify a installation prefix:
```bash
cmake -D CMAKE_INSTALL_PREFIX=~/opt/mdtappexample/release ../../
```

To avoid specifying compiler flags, it is also possible to use a cache file:
```bash
cmake -C ../../cmake/caches/ReleaseGcc.cmake -D MDT_PREFIX_PATH=~/opt/mdt/release ../../
```

Build (-j4 is for parallel build, allowing max. 4 processes):
```bash
make -j4
```

Try to run the application:
```bash
src/mdtappexample
```


You can also try to generate a archive:
```bash
cpack -G TBZ2 .
```

The generated archive should contain the application,
as well as its dependencies.
Note that Mdt provides some tools to fetch dependencies,
but this is currently experimental.

For more informations about how to deploy application,
a interesting start is [Qt for Linux - Deployment](http://doc.qt.io/qt-5/linux-deployment.html).

## Build the application on Windows

For this section, it will be considered that the application source tree is: C:\Users\You\Documents\HelloWorld.

In the root of the source tree, create a directory called "build", and a subdirectory called "release".

Open a command prompt and cd to the created directory.
Call the mdtenv.bat so that the compiler, Qt5 and Mdt are available in the PATH.

Note: the mdtenv.bat script was generated during installation of Mdt.
See [Install Mdt](#install-mdt) step for more details.

Initialzise the build:
```bash
%HOMEPATH%\Documents\opt\Mdt\Mdt0-0.3.6-Qt5.9-Windows-GNU-i386\mdtenv.bat
cmake -G "MinGW Makefiles" -D MDT_PREFIX_PATH="%HOMEPATH%\Documents\opt\Mdt\Mdt0-0.3.6-Qt5.9-Windows-GNU-i386" ..\..\
```

To avoid specifying compiler flags, it is also possible to use a cache file:
```bash
%HOMEPATH%\Documents\opt\Mdt\Mdt0-0.3.6-Qt5.9-Windows-GNU-i386\mdtenv.bat
cmake -G "MinGW Makefiles" -C ..\..\cmake\caches\ReleaseGcc.cmake -D MDT_PREFIX_PATH="%HOMEPATH%\Documents\opt\Mdt\Mdt0-0.3.6-Qt5.9-Windows-GNU-i386" ..\..\
```

Build:
```bash
mingw32-make -j4
```

You should be able to run the application
from the current command line prompt:
```bash
bin\mdtappexample.exe
```

To execute it outside current command prompt,
the application must be shipped with all its required dependencies
(mainly dlls)

Mdt has some experimental stuff to copy dependecies
and install them. You can try to generate a ZIP archive,
extract it, an run the application.

To generate a ZIP archive:
```bash
cpack -G ZIP .
```

For more informations about how to deploy application,
a interesting start is [Qt for Windows - Deployment](http://doc.qt.io/qt-5/windows-deployment.html).


# OLD stuff


## A HelloWorld example

Take a simple HelloWorld example.
Source file HelloWorld.cpp could be this:
```cpp
#include <Mdt/ItemModel/VariantTableModel.h>
#include <QTableView>
#include <QApplication>

using namespace Mdt::ItemModel;

int main(int argc, char **argv)
{
  QApplication app(argc, argv);
  VariantTableModel model;
  QTableView view;

  view.setModel(&model);
  view.show();
  model.populate(3, 2);

  return app.exec();
}
```

Write a CMakeLists.txt file:
```cmake
cmake_minimum_required(VERSION 3.2)

project(HelloWorld VERSION 0.1.0)

# Specify where to find Mdt
# Using a custom MDT_PREFIX_PATH has some advantages:
# - It solves the problem that CMAKE_PREFIX_PATH is ignored when cross-compiling with MXE
if(MDT_PREFIX_PATH)
  list(APPEND CMAKE_PREFIX_PATH "${MDT_PREFIX_PATH}")
endif()

# Specify where to find Qt5
if(QT_PREFIX_PATH)
  list(APPEND CMAKE_PREFIX_PATH "${QT_PREFIX_PATH}")
endif()

# Find Mdt CMake modules
find_package(MdtCMakeModules REQUIRED)

# On Windows, generate en env script
# The generated script will setup the PATH,
# like qtenv2.bat does.
include(MdtGenerateEnvScript)
mdt_generate_env_script(DESTINATION "${CMAKE_BINARY_DIR}")

# On Windows, RPATH do not exist
# To be able to run the application from the build tree,
# or run the unit tests, we have to put all binaries in the same directory
if(WIN32)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
endif()

# Thread support
find_package(Threads REQUIRED)

find_package(Qt5 COMPONENTS Widgets)
find_package(Mdt0 COMPONENTS ItemModel)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Rules to compile the application
# On Windows, we want a GUI executable, not a console
if(WIN32)
  add_executable(helloworld WIN32 HelloWorld.cpp)
else()
  add_executable(helloworld HelloWorld.cpp)
endif()
target_link_libraries(helloworld Mdt0::ItemModel Qt5::Widgets)

# Rules to install the application
install(
  TARGETS helloworld
  RUNTIME DESTINATION bin
)

# Rules to install application's dependencies
# Note that this is currently experimental
include(MdtDependenciesUtils)
find_package(mdtcpbindeps)
set_target_properties(helloworld PROPERTIES INSTALL_RPATH "\$ORIGIN/../lib")
mdt_install_binary_dependencies(
  TARGET helloworld
  SEARCH_FIRST_PATH_PREFIX_LIST "${CMAKE_PREFIX_PATH}"
)

# This must be added after all install() rules
include(CPack)
```




## Using icons

Internally, Mdt uses [QIcon::fromTheme()](http://doc.qt.io/qt-5/qicon.html#fromTheme)
for elements that displays icons.
This method works out of the box on Linux-X11.

To make it also work on other platforms,
we have to provide a set of icons that are compatible with the
[freedesktop.org icon theme specifications](https://specifications.freedesktop.org/icon-theme-spec/icon-theme-spec-latest.html) .

Mdt provides a copy for some compatible icon themes, like:
 - [Oxygen icons](https://github.com/KDE/oxygen-icons)


### Use icons for which Mdt provides a copy

At first, tell Qt where to find the icons.
For example, in main():
```cpp
#include <QApplication>
#include <QIcon>
#include <QStringList>

int main(int argc, char **argv)
{
  QApplication app(argc, argv);

  auto themeSearchPaths = QIcon::themeSearchPaths();
  themeSearchPaths.append("../share/icons");
  themeSearchPaths.removeDuplicates();
  QIcon::setThemeSearchPaths(themeSearchPaths);
  QIcon::setThemeName("Oxygen");

  return app.exec();
}
```

Then, add a install() rule in the CMakeLists.txt:
```cmake
# Rules to install icons
if(MDT_PREFIX_PATH)
  install(
    DIRECTORY "${MDT_PREFIX_PATH}/share/icons/oxygen"
    DESTINATION "share/icons"
  )
endif()
```

Note that the icons are only available once the application is installed.

## Translations

Mdt uses [Qt Linguist](http://doc.qt.io/qt-5/qtlinguist-index.html)
for translations.

### Translate your own application

In your project, create a subdirectory named translations .

In the main CMakeLists.txt,
specify the supported languages, add this subdirectory:
```cmake
# List of targeted translations
# This is used by MdtAddTranslations.cmake module
set(TRANSLATION_LANGUAGES en fr de)
include(MdtAddTranslations)

add_subdirectory(translations)
```

In the translations subdirectory, create a CMakeLists.txt file:
```cmake
# Avoid removing TS files by make clean
set_directory_properties(PROPERTIES CLEAN_NO_CUSTOM 1)

mdt_add_translations(
  TARGET helloworld
  SOURCES_DIRECTORY ../src
  TS_FILES_DIRECTORY .
  INSTALL_DESTINATION translations
)
```

## TODO Document main()

### TODO install Mdt qm files

### TODO install Qt5 qm files



