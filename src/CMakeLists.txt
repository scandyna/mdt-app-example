
set(SOURCE_FILES
  MainWindow.cpp
  main.cpp
)

find_package(Qt5 COMPONENTS Widgets)
find_package(Mdt0 COMPONENTS ItemModel)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Rules to compile the application
# On Windows, we want a GUI executable, not a console
if(WIN32)
  add_executable(mdtappexample WIN32 ${SOURCE_FILES})
else()
  add_executable(mdtappexample ${SOURCE_FILES})
endif()
target_link_libraries(mdtappexample Mdt0::ItemModel Qt5::Widgets)

# Rules to install the application
install(
  TARGETS mdtappexample
  RUNTIME DESTINATION bin
)
