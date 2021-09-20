#ifndef SPLINE_H
#define SPLINE_H

#include <QPaintEvent>

// 样条部分的设计与实现部分参考老师的PPT

class Spline
{
public:
    // grain为每两个控制点之间的插值点数目，tension为通过控制点位置的曲线平滑程度
    Spline(QPoint p[100], int n, int grain, float tension);    // 构造函数：创建样条曲线
    ~Spline();

    QPoint spline[2056];    // 插值点数组

private:
    void CubicSpline(int np, QPoint* konts, int grain, float tension);      // 计算插值点
    void getCardinalMatrix(float tao);                                      // 根据tension计算Cardinal矩阵系数
    float Matrix(float a, float b, float c, float d, float u);              // 矩阵运算

    QPoint knots[1000];          // 控制点数组
    float m[16];            // 储存Cardinal矩阵
};

#endif // SPLINE_H
