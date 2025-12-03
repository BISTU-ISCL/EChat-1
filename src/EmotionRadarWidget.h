#pragma once

#include <QColor>
#include <QMap>
#include <QPainterPath>
#include <QVariantList>
#include <QWidget>

// 情绪雷达图控件，支持 8 类表情默认标签并可自定义
class EmotionRadarWidget : public QWidget {
    Q_OBJECT

    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
    Q_PROPERTY(QStringList labels READ labels WRITE setLabels NOTIFY labelsChanged)
    Q_PROPERTY(QVariantList values READ values WRITE setValues NOTIFY valuesChanged)
    Q_PROPERTY(double maxValue READ maxValue WRITE setMaxValue NOTIFY maxValueChanged)
    Q_PROPERTY(int gridLines READ gridLines WRITE setGridLines NOTIFY gridLinesChanged)
    Q_PROPERTY(int margin READ margin WRITE setMargin NOTIFY marginChanged)

    Q_PROPERTY(QColor fillColor READ fillColor WRITE setFillColor NOTIFY fillColorChanged)
    Q_PROPERTY(QColor strokeColor READ strokeColor WRITE setStrokeColor NOTIFY strokeColorChanged)
    Q_PROPERTY(QColor pointColor READ pointColor WRITE setPointColor NOTIFY pointColorChanged)
    Q_PROPERTY(QColor gridColor READ gridColor WRITE setGridColor NOTIFY gridColorChanged)
    Q_PROPERTY(QColor labelColor READ labelColor WRITE setLabelColor NOTIFY labelColorChanged)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged)

    Q_PROPERTY(bool showPoints READ showPoints WRITE setShowPoints NOTIFY showPointsChanged)

public:
    explicit EmotionRadarWidget(QWidget *parent = nullptr);

    QString title() const;             // 获取标题
    QStringList labels() const;        // 获取标签列表
    QVariantList values() const;       // 获取当前数值
    double maxValue() const;           // 获取最大刻度值
    int gridLines() const;             // 获取网格圈数
    int margin() const;                // 获取内边距

    QColor fillColor() const;          // 获取填充颜色
    QColor strokeColor() const;        // 获取描边颜色
    QColor pointColor() const;         // 获取数据点颜色
    QColor gridColor() const;          // 获取网格线颜色
    QColor labelColor() const;         // 获取标签颜色
    QColor backgroundColor() const;    // 获取背景色

    bool showPoints() const;           // 是否显示每个顶点的圆点

    QSize sizeHint() const override;   // 默认控件尺寸提示

public slots:
    void setTitle(const QString &title);             // 设置标题
    void setLabels(const QStringList &labels);       // 设置标签列表
    void setValues(const QVariantList &values);      // 设置原始数值
    void setMaxValue(double maxValue);               // 设置最大刻度
    void setGridLines(int count);                    // 设置网格圈数
    void setMargin(int margin);                      // 设置绘制边距

    void setFillColor(const QColor &color);          // 设置填充颜色
    void setStrokeColor(const QColor &color);        // 设置描边颜色
    void setPointColor(const QColor &color);         // 设置数据点颜色
    void setGridColor(const QColor &color);          // 设置网格线颜色
    void setLabelColor(const QColor &color);         // 设置标签颜色
    void setBackgroundColor(const QColor &color);    // 设置背景色

    void setShowPoints(bool enabled);                // 设置是否显示顶点圆点

    void setEmotionValue(const QString &emotion, double value);     // 设置指定情绪值
    void setEmotionScores(const QMap<QString, double> &scores);     // 批量设置情绪值

signals:
    void titleChanged();
    void labelsChanged();
    void valuesChanged();
    void maxValueChanged();
    void gridLinesChanged();
    void marginChanged();

    void fillColorChanged();
    void strokeColorChanged();
    void pointColorChanged();
    void gridColorChanged();
    void labelColorChanged();
    void backgroundColorChanged();
    void showPointsChanged();

protected:
    void paintEvent(QPaintEvent *event) override;    // 绘制事件

private:
    void normalizeValues();                          // 校正数值范围与长度
    QPointF valueToPoint(int index, double value, double radius) const; // 将值转换到坐标

    QString m_title;
    QStringList m_labels;
    QVariantList m_values;
    double m_maxValue {1.0};
    int m_gridLines {5};
    int m_margin {24};

    QColor m_fillColor {QColor(0, 122, 204, 120)};
    QColor m_strokeColor {QColor(0, 122, 204)};
    QColor m_pointColor {QColor(255, 255, 255)};
    QColor m_gridColor {QColor(160, 160, 160)};
    QColor m_labelColor {QColor(60, 60, 60)};
    QColor m_backgroundColor {QColor(250, 250, 250)};

    bool m_showPoints {true};
};

