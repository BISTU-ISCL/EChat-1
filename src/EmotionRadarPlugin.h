#pragma once

#include <QtUiPlugin/QDesignerCustomWidgetInterface>
#include <QObject>

// Qt Designer 插件包装类，用于将 EmotionRadarWidget 暴露到设计器
class EmotionRadarPlugin : public QObject, public QDesignerCustomWidgetInterface {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QDesignerCustomWidgetInterface" FILE "emotionradarplugin.json")
    Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
    explicit EmotionRadarPlugin(QObject *parent = nullptr);

    QWidget *createWidget(QWidget *parent) override;
    QString name() const override;
    QString group() const override;
    QIcon icon() const override;
    QString toolTip() const override;
    QString whatsThis() const override;
    bool isContainer() const override;
    QString includeFile() const override;
    QString domXml() const override;
    bool isInitialized() const override;
    void initialize(QDesignerFormEditorInterface *core) override;

private:
    bool m_initialized {false};
};

