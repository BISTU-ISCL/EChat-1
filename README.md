# Emotion Radar Qt 组件

这是一个基于 Qt Widgets 的自定义雷达图控件，专门用来展示 8 类表情识别结果。它提供丰富的属性用于颜色、尺寸、刻度等外观配置，同时提供 Qt Designer 插件，可以拖拽到前面板直接使用，也支持在代码中进行自定义操作（如动态更新分数、修改标签）。

## 主要特性
- 默认 8 类表情（Happy、Sad、Angry、Fearful、Disgust、Surprised、Neutral、Contempt），可自定义标签和数值。
- 丰富的外观属性：填充颜色、描边颜色、点颜色、网格颜色、背景色、标题、网格线数量、边距、是否显示数据点等。
- 提供 `setEmotionValue`、`setEmotionScores` 等便捷接口，便于从推理结果直接更新雷达图。
- Qt Designer 插件，支持在设计器中拖拽使用；同一个核心控件也可以在代码中单独引入。

## 文件结构
- `src/EmotionRadarWidget.h/.cpp`：核心雷达图控件实现。
- `src/EmotionRadarPlugin.h/.cpp`：Qt Designer 插件封装，注册控件以便拖拽使用。
- `CMakeLists.txt`：同时兼容 Qt 5/6 Widgets + Designer 的构建脚本。

## 构建与安装（CMake）
```bash
mkdir -p build && cd build
cmake ..
cmake --build .
cmake --install . --prefix <安装路径>
```

### Qt Designer 插件部署
- **Linux/macOS**：将生成的 `emotionradardesigner` 库放入 `${QT_PLUGIN_PATH}/designer/`（或 Qt 安装目录下的相应 `plugins/designer/` 文件夹）。
- **Windows**：将生成的 `emotionradardesigner.dll` 放到 `C:/Qt/<版本>/plugins/designer/`。
- 重新启动 Qt Designer，即可在 "Analytics" 分组下找到 `EmotionRadarWidget`，拖入表单后可在属性面板配置颜色、网格、标题等属性。

### 代码中直接使用
```cpp
#include "EmotionRadarWidget.h"

EmotionRadarWidget *radar = new EmotionRadarWidget(parent);
radar->setEmotionScores({{"Happy", 0.8}, {"Sad", 0.1}});
radar->setFillColor(QColor("#3fa7ff"));
radar->setStrokeColor(Qt::blue);
```

## 关键属性列表
- `title`：标题文本。
- `labels`：情绪标签列表（默认 8 类，可扩展）。
- `values`：数值（`QVariantList`），与标签顺序对应。
- `maxValue`：最大刻度，默认 1.0，用于归一化。
- `gridLines`：网格圈数，默认 5。
- `margin`：绘制内边距，默认 24 像素。
- `fillColor`、`strokeColor`、`pointColor`、`gridColor`、`labelColor`、`backgroundColor`：配色控制。
- `showPoints`：是否显示每个维度的圆点。

## 示例场景
- 将模型输出的 8 维表情概率（或分值）直接传入 `setEmotionScores` 即可实时更新雷达图。
- 使用 Qt Designer 拖拽控件，配合属性面板调整配色、网格密度、标题等视觉效果，快速搭建表情分析前端面板。

