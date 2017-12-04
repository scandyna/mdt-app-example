
find_package(Qt5 COMPONENTS Test Widgets)
find_package(Mdt0 COMPONENTS ItemModel)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(SOURCE_FILES
  "${CMAKE_SOURCE_DIR}/src/MainWindow.cpp"
  src/RunTest.cpp
)

add_executable(runtest ${SOURCE_FILES})
target_link_libraries(runtest Qt5::Widgets Mdt0::ItemModel)
set_target_properties(runtest PROPERTIES INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/src")
add_test(NAME RunTest COMMAND runtest)
