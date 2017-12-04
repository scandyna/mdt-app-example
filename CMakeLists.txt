cmake_minimum_required(VERSION 3.2)

project(MdtAppExample VERSION 0.1.0)

# Specify where to find Mdt
# Using a custom MDT_PREFIX_PATH has some advantages:
# - It solves the problem that CMAKE_PREFIX_PATH is ignored when cross-compiling with MXE
if(MDT_PREFIX_PATH)
  list(APPEND CMAKE_PREFIX_PATH "${MDT_PREFIX_PATH}")
endif()

# Find Mdt CMake modules
find_package(MdtCMakeModules REQUIRED)

# Get path to the Qt5 library
include(MdtQtPath)

# On Windows, RPATH do not exist
# To be able to run the application from the build tree,
# or run the unit tests, we have to put all binaries in the same directory
if(WIN32)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
endif()

# Thread support
find_package(Threads REQUIRED)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

add_subdirectory(src)

# # Rules to install application's dependencies
# # Note that this is currently experimental
# include(MdtDependenciesUtils)
# find_package(mdtcpbindeps)
# set_target_properties(mdtappexample PROPERTIES INSTALL_RPATH "\$ORIGIN/../lib")
# mdt_install_binary_dependencies(
#   TARGET mdtappexample
#   SEARCH_FIRST_PATH_PREFIX_LIST "${CMAKE_PREFIX_PATH}"
# )

# This must be added after all install() rules
include(CPack)
