#include "EmotionRadarWidget.h"

#include <QtMath>
#include <QPainter>
#include <QPainterPath>

namespace {
QStringList defaultEmotions()
{
    return {QStringLiteral("Happy"), QStringLiteral("Sad"),   QStringLiteral("Angry"),
            QStringLiteral("Fearful"), QStringLiteral("Disgust"), QStringLiteral("Surprised"),
            QStringLiteral("Neutral"), QStringLiteral("Contempt")};
}
}

EmotionRadarWidget::EmotionRadarWidget(QWidget *parent)
    : QWidget(parent)
    , m_labels(defaultEmotions())
    , m_values(QVariantList(defaultEmotions().size(), 0.0))
    , m_title(tr("Emotion Radar"))
{
    setMinimumSize({200, 200});
}

QString EmotionRadarWidget::title() const
{
    return m_title;
}

QStringList EmotionRadarWidget::labels() const
{
    return m_labels;
}

QVariantList EmotionRadarWidget::values() const
{
    return m_values;
}

double EmotionRadarWidget::maxValue() const
{
    return m_maxValue;
}

int EmotionRadarWidget::gridLines() const
{
    return m_gridLines;
}

int EmotionRadarWidget::margin() const
{
    return m_margin;
}

QColor EmotionRadarWidget::fillColor() const
{
    return m_fillColor;
}

QColor EmotionRadarWidget::strokeColor() const
{
    return m_strokeColor;
}

QColor EmotionRadarWidget::pointColor() const
{
    return m_pointColor;
}

QColor EmotionRadarWidget::gridColor() const
{
    return m_gridColor;
}

QColor EmotionRadarWidget::labelColor() const
{
    return m_labelColor;
}

QColor EmotionRadarWidget::backgroundColor() const
{
    return m_backgroundColor;
}

bool EmotionRadarWidget::showPoints() const
{
    return m_showPoints;
}

QSize EmotionRadarWidget::sizeHint() const
{
    return {320, 320};
}

void EmotionRadarWidget::setTitle(const QString &title)
{
    if (title == m_title)
        return;
    m_title = title;
    update();
    emit titleChanged();
}

void EmotionRadarWidget::setLabels(const QStringList &labels)
{
    if (labels == m_labels || labels.isEmpty())
        return;

    m_labels = labels;
    m_values = QVariantList(m_labels.size(), 0.0);
    normalizeValues();
    update();
    emit labelsChanged();
}

void EmotionRadarWidget::setValues(const QVariantList &values)
{
    m_values = values;
    normalizeValues();
    update();
    emit valuesChanged();
}

void EmotionRadarWidget::setMaxValue(double maxValue)
{
    if (qFuzzyCompare(m_maxValue, maxValue) || maxValue <= 0.0)
        return;
    m_maxValue = maxValue;
    normalizeValues();
    update();
    emit maxValueChanged();
}

void EmotionRadarWidget::setGridLines(int count)
{
    if (count == m_gridLines || count < 1)
        return;
    m_gridLines = count;
    update();
    emit gridLinesChanged();
}

void EmotionRadarWidget::setMargin(int margin)
{
    if (margin == m_margin || margin < 0)
        return;
    m_margin = margin;
    update();
    emit marginChanged();
}

void EmotionRadarWidget::setFillColor(const QColor &color)
{
    if (color == m_fillColor)
        return;
    m_fillColor = color;
    update();
    emit fillColorChanged();
}

void EmotionRadarWidget::setStrokeColor(const QColor &color)
{
    if (color == m_strokeColor)
        return;
    m_strokeColor = color;
    update();
    emit strokeColorChanged();
}

void EmotionRadarWidget::setPointColor(const QColor &color)
{
    if (color == m_pointColor)
        return;
    m_pointColor = color;
    update();
    emit pointColorChanged();
}

void EmotionRadarWidget::setGridColor(const QColor &color)
{
    if (color == m_gridColor)
        return;
    m_gridColor = color;
    update();
    emit gridColorChanged();
}

void EmotionRadarWidget::setLabelColor(const QColor &color)
{
    if (color == m_labelColor)
        return;
    m_labelColor = color;
    update();
    emit labelColorChanged();
}

void EmotionRadarWidget::setBackgroundColor(const QColor &color)
{
    if (color == m_backgroundColor)
        return;
    m_backgroundColor = color;
    update();
    emit backgroundColorChanged();
}

void EmotionRadarWidget::setShowPoints(bool enabled)
{
    if (enabled == m_showPoints)
        return;
    m_showPoints = enabled;
    update();
    emit showPointsChanged();
}

void EmotionRadarWidget::setEmotionValue(const QString &emotion, double value)
{
    int index = m_labels.indexOf(emotion);
    if (index < 0)
        return;

    if (m_values.size() <= index)
        m_values.resize(m_labels.size());

    m_values[index] = value;
    normalizeValues();
    update();
    emit valuesChanged();
}

void EmotionRadarWidget::setEmotionScores(const QMap<QString, double> &scores)
{
    for (auto it = scores.constBegin(); it != scores.constEnd(); ++it)
        setEmotionValue(it.key(), it.value());
}

void EmotionRadarWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(rect(), m_backgroundColor);

    const int count = m_labels.size();
    if (count == 0)
        return;

    const QPointF center(width() / 2.0, height() / 2.0 + 10);
    const double radius = qMax(10.0, qMin(width(), height()) / 2.0 - m_margin);
    painter.save();
    painter.setPen(QPen(m_gridColor, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

    for (int i = 1; i <= m_gridLines; ++i) {
        const double r = radius * i / m_gridLines;
        QPolygonF polygon;
        for (int j = 0; j < count; ++j)
            polygon << valueToPoint(j, r, radius) + center;
        painter.drawPolygon(polygon);
    }

    for (int i = 0; i < count; ++i) {
        painter.drawLine(center, valueToPoint(i, radius, radius) + center);
    }

    painter.restore();

    painter.save();
    painter.setPen(QPen(m_labelColor, 1));
    QFont font = painter.font();
    font.setBold(true);
    painter.setFont(font);

    const int labelOffset = 16;
    for (int i = 0; i < count; ++i) {
        QPointF pos = valueToPoint(i, radius + labelOffset, radius) + center;
        QRectF textRect(pos.x() - 40, pos.y() - 12, 80, 24);
        painter.drawText(textRect, Qt::AlignCenter, m_labels.value(i));
    }
    painter.restore();

    painter.save();
    QPolygonF valuePolygon;
    for (int i = 0; i < count; ++i) {
        const double value = m_values.value(i, 0.0).toDouble();
        valuePolygon << valueToPoint(i, value, radius) + center;
    }

    painter.setBrush(m_fillColor);
    painter.setPen(QPen(m_strokeColor, 2));
    painter.drawPolygon(valuePolygon);

    if (m_showPoints) {
        painter.setBrush(m_pointColor);
        painter.setPen(QPen(m_strokeColor, 1));
        for (const QPointF &point : valuePolygon)
            painter.drawEllipse(point, 4, 4);
    }

    painter.restore();

    painter.save();
    painter.setPen(QPen(m_labelColor, 1));
    QFont titleFont = painter.font();
    titleFont.setBold(true);
    titleFont.setPointSize(titleFont.pointSize() + 2);
    painter.setFont(titleFont);
    painter.drawText(QRectF(0, 0, width(), 24), Qt::AlignCenter, m_title);
    painter.restore();
}

void EmotionRadarWidget::normalizeValues()
{
    if (m_labels.isEmpty())
        return;

    const int count = m_labels.size();
    if (m_values.size() != count) {
        QVariantList adjusted(count, 0.0);
        const int copyCount = qMin(count, m_values.size());
        for (int i = 0; i < copyCount; ++i)
            adjusted[i] = m_values.at(i);
        m_values = adjusted;
    }

    for (int i = 0; i < count; ++i) {
        double v = m_values.at(i).toDouble();
        if (v < 0.0)
            v = 0.0;
        if (v > m_maxValue)
            v = m_maxValue;
        m_values[i] = v;
    }
}

QPointF EmotionRadarWidget::valueToPoint(int index, double value, double radius) const
{
    const int count = m_labels.size();
    if (count == 0)
        return {};

    const double angle = -M_PI_2 + index * (2 * M_PI / count);
    const double scaled = (radius * value) / m_maxValue;
    return {scaled * qCos(angle), scaled * qSin(angle)};
}

