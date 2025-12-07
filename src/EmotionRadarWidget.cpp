#include "EmotionRadarWidget.h"

#include <QtMath>
#include <QtGlobal>
#include <QPainter>
#include <QPainterPath>

namespace {
// 默认的 8 类表情标签
QStringList defaultEmotions()
{
    return {QStringLiteral("Happy"), QStringLiteral("Sad"),   QStringLiteral("Angry"),
            QStringLiteral("Fearful"), QStringLiteral("Disgust"), QStringLiteral("Surprised"),
            QStringLiteral("Neutral"), QStringLiteral("Contempt")};
}
} // namespace

EmotionRadarWidget::EmotionRadarWidget(QWidget *parent)
    : QWidget(parent)
    , m_labels(defaultEmotions())
    , m_values(QVariantList(defaultEmotions().size(), 0.0))
    , m_title(tr("Emotion Radar"))
{
    setMinimumSize({200, 200}); // 给出一个合适的最小值，避免被压缩到太小
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
    m_values = QVariantList(m_labels.size(), 0.0); // 重置值列表，保持长度一致
    normalizeValues();                              // 归一化数值到合法范围
    update();
    emit labelsChanged();
}

void EmotionRadarWidget::setValues(const QVariantList &values)
{
    m_values = values;   // 接收原始数值
    normalizeValues();   // 自动截断到 0~maxValue，并匹配标签长度
    update();
    emit valuesChanged();
}

void EmotionRadarWidget::setMaxValue(double maxValue)
{
    if (qFuzzyCompare(m_maxValue, maxValue) || maxValue <= 0.0)
        return;
    m_maxValue = maxValue;
    normalizeValues(); // 数值上限变化后需要重新修正
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
    int index = m_labels.indexOf(emotion); // 查找对应情绪索引
    if (index < 0)
        return;

    if (m_values.size() <= index)
        m_values.resize(m_labels.size());

    m_values[index] = value; // 写入单个值
    normalizeValues();       // 归一化
    update();
    emit valuesChanged();
}

void EmotionRadarWidget::setEmotionScores(const QMap<QString, double> &scores)
{
    // 批量写入所有情绪
    for (auto it = scores.constBegin(); it != scores.constEnd(); ++it)
        setEmotionValue(it.key(), it.value());
}

void EmotionRadarWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing); // 开启抗锯齿
    painter.fillRect(rect(), m_backgroundColor);   // 绘制背景

    // 根据当前窗口尺寸进行自适应缩放，确保缩放时线宽、字体、间距保持视觉一致
    const double baseSize = 320.0; // 与 sizeHint 对齐的参考尺寸
    const double scale = qBound(0.6, qMin(width(), height()) / baseSize, 2.4);
    const double margin = m_margin * scale;

    const int count = m_labels.size();
    if (count == 0)
        return;

    const QPointF center(width() / 2.0, height() / 2.0 + 10 * scale);                   // 极坐标中心
    const double radius = qMax(10.0, qMin(width(), height()) / 2.0 - margin);           // 有效半径
    painter.save();

    const qreal gridPenWidth = qMax<qreal>(1.0, 1.0 * scale);
    painter.setPen(QPen(m_gridColor, gridPenWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

    // 绘制同心网格多边形
    for (int i = 1; i <= m_gridLines; ++i) {
        const double r = radius * i / m_gridLines;
        QPolygonF polygon;
        for (int j = 0; j < count; ++j)
            polygon << valueToPoint(j, r, radius) + center;
        painter.drawPolygon(polygon);
    }

    // 绘制每个维度的径向线
    for (int i = 0; i < count; ++i) {
        painter.drawLine(center, valueToPoint(i, radius, radius) + center);
    }

    painter.restore();

    painter.save();
    painter.setPen(QPen(m_labelColor, 1));
    QFont font = painter.font();
    font.setBold(true);
    font.setPointSizeF(font.pointSizeF() * scale);
    painter.setFont(font);

    const double labelOffset = 16.0 * scale;
    // 绘制标签文本
    for (int i = 0; i < count; ++i) {
        QPointF pos = valueToPoint(i, radius + labelOffset, radius) + center;
        QRectF textRect(pos.x() - 40 * scale, pos.y() - 12 * scale, 80 * scale, 24 * scale);
        painter.drawText(textRect, Qt::AlignCenter, m_labels.value(i));
    }
    painter.restore();

    painter.save();
    QPolygonF valuePolygon;
    // 计算每个值的顶点坐标
    for (int i = 0; i < count; ++i) {
        const double value = m_values.value(i, 0.0).toDouble();
        valuePolygon << valueToPoint(i, value, radius) + center;
    }

    // 填充数据区域
    painter.setBrush(m_fillColor);
    painter.setPen(QPen(m_strokeColor, qMax<qreal>(1.0, 2.0 * scale)));
    painter.drawPolygon(valuePolygon);

    // 绘制节点圆点
    if (m_showPoints) {
        painter.setBrush(m_pointColor);
        painter.setPen(QPen(m_strokeColor, qMax<qreal>(1.0, 1.0 * scale)));
        for (const QPointF &point : valuePolygon)
            painter.drawEllipse(point, 4 * scale, 4 * scale);
    }

    painter.restore();

    painter.save();
    painter.setPen(QPen(m_labelColor, 1));
    QFont titleFont = painter.font();
    titleFont.setBold(true);
    titleFont.setPointSizeF(titleFont.pointSizeF() * scale + 2);
    painter.setFont(titleFont);
    painter.drawText(QRectF(0, 0, width(), 24 * scale), Qt::AlignCenter, m_title);
    painter.restore();
}

void EmotionRadarWidget::normalizeValues()
{
    if (m_labels.isEmpty())
        return;

    const int count = m_labels.size();
    if (m_values.size() != count) {
        QVariantList adjusted(count, 0.0); // 确保与标签长度一致
        const int copyCount = qMin(count, m_values.size());
        for (int i = 0; i < copyCount; ++i)
            adjusted[i] = m_values.at(i);
        m_values = adjusted;
    }

    for (int i = 0; i < count; ++i) {
        double v = m_values.at(i).toDouble();
        if (v < 0.0)
            v = 0.0;           // 下限保护
        if (v > m_maxValue)
            v = m_maxValue;    // 上限保护
        m_values[i] = v;
    }
}

QPointF EmotionRadarWidget::valueToPoint(int index, double value, double radius) const
{
    const int count = m_labels.size();
    if (count == 0)
        return {};

    const double angle = -M_PI_2 + index * (2 * M_PI / count);    // 从顶部开始顺时针
    const double scaled = (radius * value) / m_maxValue;          // 线性缩放到半径
    return {scaled * qCos(angle), scaled * qSin(angle)};          // 转换到平面坐标
}

