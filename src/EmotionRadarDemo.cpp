// 简单示例程序：演示 EmotionRadarWidget 的创建与动态更新
#include <QApplication>
#include <QVBoxLayout>
#include <QTimer>
#include <QRandomGenerator>
#include <QMap>

#include "EmotionRadarWidget.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget window;
    window.setWindowTitle(QObject::tr("表情雷达图 Demo"));
    auto *layout = new QVBoxLayout(&window);

    // 创建雷达图控件
    auto *radar = new EmotionRadarWidget(&window);
    radar->setTitle(QObject::tr("实时情绪分布"));
    radar->setFillColor(QColor(63, 167, 255, 120)); // 半透明填充
    radar->setStrokeColor(QColor(63, 167, 255));    // 轮廓线颜色
    radar->setPointColor(Qt::white);                // 顶点点颜色

    layout->addWidget(radar);

    // 模拟模型输出：定时刷新 8 类表情得分
    auto *timer = new QTimer(&window);
    QObject::connect(timer, &QTimer::timeout, [&]() {
        QMap<QString, double> scores;
        auto *rng = QRandomGenerator::global();
        scores.insert("Happy", rng->bounded(0.0, 1.0));
        scores.insert("Sad", rng->bounded(0.0, 1.0));
        scores.insert("Angry", rng->bounded(0.0, 1.0));
        scores.insert("Fearful", rng->bounded(0.0, 1.0));
        scores.insert("Disgust", rng->bounded(0.0, 1.0));
        scores.insert("Surprised", rng->bounded(0.0, 1.0));
        scores.insert("Neutral", rng->bounded(0.0, 1.0));
        scores.insert("Contempt", rng->bounded(0.0, 1.0));
        radar->setEmotionScores(scores); // 批量写入到雷达图
    });
    timer->start(1500); // 每 1.5 秒刷新一次

    window.resize(480, 420);
    window.show();

    return app.exec();
}
