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

# Enable testing
# Must be placed before any add_subdirectory() command, else tests that are defined in sub-directories will be ignored
enable_testing()

add_subdirectory(src)
add_subdirectory(tests)

if(CMAKE_BUILD_TYPE MATCHES "Debug")
  message("DEBUG build")
  set(debug_file_name_postfix "-debug")
else()
  set(debug_file_name_postfix "")
endif()
set(CPACK_PACKAGE_FILE_NAME "${PROJECT_NAME}-${PROJECT_VERSION}-${CMAKE_SYSTEM_NAME}-${CMAKE_CXX_COMPILER_ID}${debug_file_name_postfix}")

# This must be added after all install() rules
include(CPack)
