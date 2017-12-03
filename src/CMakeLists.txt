
# Rules to compile the application
# On Windows, we want a GUI executable, not a console
if(WIN32)
  add_executable(mdtappexample WIN32 main.cpp)
else()
  add_executable(mdtappexample main.cpp)
endif()
target_link_libraries(mdtappexample Mdt0::ItemModel Qt5::Widgets)

# Rules to install the application
install(
  TARGETS mdtappexample
  RUNTIME DESTINATION bin
)
