#pragma execution_character_set("utf-8")

#ifndef WIDGET_H
#define WIDGET_H

#include "spline.h"
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QLabel>
#include <QPropertyAnimation>
#include <QTimer>
#include <QPoint>
#include <QPixmap>
#include <QPixmapCache>
#include <iostream>
#include <QImage>
#include <QDebug>
#include <qmath.h>
#include <QMatrix>

#define PI 3.14159265

using namespace std;

namespace Ui
{
    class Widget;
}

// 绘制模式与状态判定
enum State {START, DRAW, POINT, PLAY, PAUSE, STOP};

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget* parent = 0);
    ~Widget();

protected:
    void mousePressEvent(QMouseEvent*);
    void paintEvent(QPaintEvent*);

private slots:
    void draw();            // 画曲线
    void show_point();      // 显示插值点
    void play();            // 播放动画
    void pause_resume();    // 动画暂停与恢复
    void clear();           // 清空
    void ani_control();     // 动画控制

private:
    Ui::Widget *ui;
    QPixmap pix;
    Spline *mSpline;

    // 控制点坐标
    QPoint p[100];

    State state;    // 绘制模式

    int n;                  // 控制点
    int part;               // 分段数
    int grain;              // 每两个控制点之间的插值点数目
    int grain_total;        // 插值点的总个数
    float tension;          // 通过控制点位置的曲线平滑程度

    // 小车及动画相关参数
    QLabel *car;
    QPropertyAnimation *ani;
    QTimer *timer;
    QImage *img;

    float speed;
    float angle;

};

#endif // WIDGET_H
