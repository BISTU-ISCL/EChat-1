#include "EmotionRadarPlugin.h"

#include "EmotionRadarWidget.h"

#include <QtPlugin>

EmotionRadarPlugin::EmotionRadarPlugin(QObject *parent)
    : QObject(parent)
{}

QWidget *EmotionRadarPlugin::createWidget(QWidget *parent)
{
    return new EmotionRadarWidget(parent); // 由设计器创建控件实例
}

QString EmotionRadarPlugin::name() const
{
    return QStringLiteral("EmotionRadarWidget");
}

QString EmotionRadarPlugin::group() const
{
    return QStringLiteral("Analytics"); // 分组名称，设计器中显示
}

QIcon EmotionRadarPlugin::icon() const
{
    return QIcon();
}

QString EmotionRadarPlugin::toolTip() const
{
    return tr("Radar chart widget for emotion recognition results"); // 鼠标悬停提示
}

QString EmotionRadarPlugin::whatsThis() const
{
    return tr("Displays up to eight emotion probabilities on a configurable radar chart."); // 帮助文本
}

bool EmotionRadarPlugin::isContainer() const
{
    return false; // 不是容器控件
}

QString EmotionRadarPlugin::includeFile() const
{
    return QStringLiteral("EmotionRadarWidget.h");
}

QString EmotionRadarPlugin::domXml() const
{
    // 在设计器中展示的 DOM 描述
    return QLatin1String(
        "<ui language=\"c++\">"
        " <widget class=\"EmotionRadarWidget\" name=\"emotionRadar\">"
        "  <property name=\"toolTip\" >"
        "   <string>Radar chart for emotion recognition</string>"
        "  </property>"
        "  <property name=\"whatsThis\" >"
        "   <string>Drop into your UI to visualise 8-class emotion scores.</string>"
        "  </property>"
        " </widget>"
        "</ui>");
}

bool EmotionRadarPlugin::isInitialized() const
{
    return m_initialized;
}

void EmotionRadarPlugin::initialize(QDesignerFormEditorInterface *core)
{
    Q_UNUSED(core);
    if (m_initialized)
        return;

    m_initialized = true; // 防止重复初始化
}

