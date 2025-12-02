#pragma once

#include <QDesignerCustomWidgetInterface>
#include <QObject>

class EmotionRadarPlugin : public QObject, public QDesignerCustomWidgetInterface {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QDesignerCustomWidgetInterface")
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

