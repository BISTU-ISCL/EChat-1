cmake_minimum_required(VERSION 3.16)
project(EmotionRadarWidget LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(GNUInstallDirs)

find_package(Qt6 COMPONENTS Widgets UiPlugin QUIET)
if (NOT Qt6_FOUND)
    find_package(Qt5 COMPONENTS Widgets Designer REQUIRED)
    set(QT_VERSION 5)
else()
    set(QT_VERSION 6)
endif()

set(WIDGET_SOURCES
    src/EmotionRadarWidget.cpp
    src/EmotionRadarWidget.h)

add_library(emotionradarwidget STATIC ${WIDGET_SOURCES})
target_include_directories(emotionradarwidget PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
if (QT_VERSION EQUAL 6)
    target_link_libraries(emotionradarwidget PUBLIC Qt6::Widgets)
else()
    target_link_libraries(emotionradarwidget PUBLIC Qt5::Widgets)
endif()

set(PLUGIN_SOURCES
    src/EmotionRadarPlugin.cpp
    src/EmotionRadarPlugin.h
    src/emotionradarplugin.json)

if (QT_VERSION EQUAL 6)
    qt_add_plugin(emotionradardesigner CLASS_NAME EmotionRadarPlugin ${PLUGIN_SOURCES})
    target_link_libraries(emotionradardesigner PRIVATE emotionradarwidget Qt6::UiPlugin Qt6::Widgets)
else()
    add_library(emotionradardesigner SHARED ${PLUGIN_SOURCES})
    target_link_libraries(emotionradardesigner PRIVATE emotionradarwidget Qt5::Designer Qt5::Widgets)
endif()

target_include_directories(emotionradardesigner PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

# 示例程序：演示 EmotionRadarWidget 的用法，可通过 -DBUILD_EMOTION_RADAR_DEMO=ON 启用
option(BUILD_EMOTION_RADAR_DEMO "Build demo application" ON)
if (BUILD_EMOTION_RADAR_DEMO)
    add_executable(emotionradar_demo src/EmotionRadarDemo.cpp)
    target_link_libraries(emotionradar_demo PRIVATE emotionradarwidget)
    if (QT_VERSION EQUAL 6)
        target_link_libraries(emotionradar_demo PRIVATE Qt6::Widgets)
    else()
        target_link_libraries(emotionradar_demo PRIVATE Qt5::Widgets)
    endif()
endif()

install(TARGETS emotionradardesigner
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(FILES src/EmotionRadarWidget.h DESTINATION include)

