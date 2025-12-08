cmake_minimum_required(VERSION 3.16)
project(EmotionRadarWidget LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(GNUInstallDirs)

# 本项目针对 Windows 上的 Qt 6.10.0 + MSVC 2022 64-bit Release 环境
find_package(Qt6 6.10.0 REQUIRED COMPONENTS Widgets Designer)

set(WIDGET_SOURCES
    src/EmotionRadarWidget.cpp
    src/EmotionRadarWidget.h)

add_library(emotionradarwidget STATIC ${WIDGET_SOURCES})
target_include_directories(emotionradarwidget PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(emotionradarwidget PUBLIC Qt6::Widgets)

set(PLUGIN_SOURCES
    src/EmotionRadarPlugin.cpp
    src/EmotionRadarPlugin.h
    src/emotionradarplugin.json)

add_library(emotionradardesigner MODULE ${PLUGIN_SOURCES})
target_link_libraries(emotionradardesigner PRIVATE emotionradarwidget Qt6::Designer Qt6::Widgets)

target_include_directories(emotionradardesigner PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

# 示例程序：演示 EmotionRadarWidget 的用法，可通过 -DBUILD_EMOTION_RADAR_DEMO=ON 启用
option(BUILD_EMOTION_RADAR_DEMO "Build demo application" ON)
if (BUILD_EMOTION_RADAR_DEMO)
    add_executable(emotionradar_demo src/EmotionRadarDemo.cpp)
    target_link_libraries(emotionradar_demo PRIVATE emotionradarwidget)
    target_link_libraries(emotionradar_demo PRIVATE Qt6::Widgets)
endif()

install(TARGETS emotionradardesigner
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(FILES src/EmotionRadarWidget.h DESTINATION include)

