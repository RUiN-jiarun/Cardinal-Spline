#include "spline.h"

// 初始化：生成Cardinal样条曲线
Spline::Spline(QPoint p[100], int n, int grain, float tension)
{
    for(int i = 1; i <= n; i++)
    {
        knots[i] = p[i-1];
    }

    // 首尾控制点要重复赋值！
    knots[0] = p[0];
    knots[n+1] = p[n-1];

    // 生成插值点
    CubicSpline(n + 2, knots, grain, tension);
}

// 根据tension生成Cardinal矩阵
void Spline::getCardinalMatrix(float tao)
{
    m[0]=-tao;   m[1]=2.-tao;  m[2]=tao-2.;   m[3]=tao;
    m[4]=2.*tao; m[5]=tao-3.;  m[6]=3.-2*tao; m[7]=-tao;
    m[8]=-tao;   m[9]=0.;     m[10]=tao;     m[11]=0.;
    m[12]=0.;   m[13]=1.;    m[14]=0.;     m[15]=0.;
}

// 矩阵运算
float Spline::Matrix(float a, float b, float c, float d, float u)
{
    float p0, p1, p2, p3;
    p0 = m[0]*a + m[1]*b + m[2]*c + m[3]*d;
    p1 = m[4]*a + m[5]*b + m[6]*c + m[7]*d;
    p2 = m[8]*a + m[9]*b + m[10]*c + m[11]*d;
    p3 = m[12]*a + m[13]*b + m[14]*c + m[15]*d;
    return (u*u*u*p0 + u*u*p1 + u*p2 + p3);
}

// 插值函数
void Spline::CubicSpline(int np, QPoint* knots, int grain, float tension)
{
    QPoint *s, *k0, *kml, *k1, *k2;
    int i, j;
    float u[50];
    getCardinalMatrix(tension);

    // 根据分段值确定u[]
    for(i = 0; i < grain; i++)
    {
        u[i] = ((float) i)/grain;
    }

    s = spline;     // 插值点数组
    kml = knots;    // 由控制点数组得到公式右边的列矩阵
    k0 = kml + 1;
    k1 = k0 + 1;
    k2 = k1 + 1;

    // 求插值点的坐标，除去前后的重合部分
    for(i = 0; i < np - 3; i++)
    {
        for(j = 0; j < grain; j++)
        {
            float tmpx = Matrix(kml->x(), k0->x(), k1->x(), k2->x(), u[j]);
            float tmpy = Matrix(kml->y(), k0->y(), k1->y(), k2->y(), u[j]);
            s->setX(tmpx);
            s->setY(tmpy);
            s++;
        }
        k0++; kml++; k1++; k2++;
    }

    // 末尾的端点
    s->setX(k0->x());
    s->setY(k0->y());
}

Spline::~Spline()
{
}
