cmake_minimum_required(VERSION 3.18)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

project(noggit-updater VERSION 0.1 LANGUAGES CXX)

find_package(Qt5 COMPONENTS Core REQUIRED)

set(app_icon_resource_windows icon.rc)

add_executable(noggit-updater
  main.cpp ${app_icon_resource_windows}
)

target_link_libraries(noggit-updater PRIVATE
    Qt5::Core
)
