#include "EmotionRadarPlugin.h"

#include "EmotionRadarWidget.h"

#include <QtPlugin>

EmotionRadarPlugin::EmotionRadarPlugin(QObject *parent)
    : QObject(parent)
{}

QWidget *EmotionRadarPlugin::createWidget(QWidget *parent)
{
    return new EmotionRadarWidget(parent);
}

QString EmotionRadarPlugin::name() const
{
    return QStringLiteral("EmotionRadarWidget");
}

QString EmotionRadarPlugin::group() const
{
    return QStringLiteral("Analytics");
}

QIcon EmotionRadarPlugin::icon() const
{
    return QIcon();
}

QString EmotionRadarPlugin::toolTip() const
{
    return tr("Radar chart widget for emotion recognition results");
}

QString EmotionRadarPlugin::whatsThis() const
{
    return tr("Displays up to eight emotion probabilities on a configurable radar chart.");
}

bool EmotionRadarPlugin::isContainer() const
{
    return false;
}

QString EmotionRadarPlugin::includeFile() const
{
    return QStringLiteral("EmotionRadarWidget.h");
}

QString EmotionRadarPlugin::domXml() const
{
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

    m_initialized = true;
}

