#pragma once

#include <QColor>
#include <QMap>
#include <QPainterPath>
#include <QVariantList>
#include <QWidget>

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

    QString title() const;
    QStringList labels() const;
    QVariantList values() const;
    double maxValue() const;
    int gridLines() const;
    int margin() const;

    QColor fillColor() const;
    QColor strokeColor() const;
    QColor pointColor() const;
    QColor gridColor() const;
    QColor labelColor() const;
    QColor backgroundColor() const;

    bool showPoints() const;

    QSize sizeHint() const override;

public slots:
    void setTitle(const QString &title);
    void setLabels(const QStringList &labels);
    void setValues(const QVariantList &values);
    void setMaxValue(double maxValue);
    void setGridLines(int count);
    void setMargin(int margin);

    void setFillColor(const QColor &color);
    void setStrokeColor(const QColor &color);
    void setPointColor(const QColor &color);
    void setGridColor(const QColor &color);
    void setLabelColor(const QColor &color);
    void setBackgroundColor(const QColor &color);

    void setShowPoints(bool enabled);

    void setEmotionValue(const QString &emotion, double value);
    void setEmotionScores(const QMap<QString, double> &scores);

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
    void paintEvent(QPaintEvent *event) override;

private:
    void normalizeValues();
    QPointF valueToPoint(int index, double value, double radius) const;

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

