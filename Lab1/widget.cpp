#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("Cardinal Spline Simulator");

    // 数据初始化
    n = 0;
    part = -1;
    state = START;
    pix = QPixmap(550, 780);

    QMatrix matrix;
    pix.fill(Qt::white);

    // 信号与槽函数对接
    timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(ani_control()));
    connect(ui->draw_pushButton, &QPushButton::clicked, this, &Widget::draw);
    connect(ui->clear_pushButton, &QPushButton::clicked, this, &Widget::clear);
    connect(ui->point_pushButton, &QPushButton::clicked, this, &Widget::show_point);
    connect(ui->play_pushButton, &QPushButton::clicked, this, &Widget::play);
    connect(ui->pause_pushButton, &QPushButton::clicked, this, &Widget::pause_resume);

    // 设置按钮状态
    ui->draw_pushButton->setEnabled(false);
    ui->clear_pushButton->setEnabled(true);
    ui->play_pushButton->setEnabled(false);
    ui->point_pushButton->setEnabled(false);
    ui->pause_pushButton->setEnabled(false);
    ui->speed_horizontalSlider->setValue(7500);
    ui->grain_spinBox->setValue(5);
    ui->tension_doubleSpinBox->setValue(0);

    // 图片素材加载
    img = new QImage(":/car.png");
    *img = img->scaled(70, 50, Qt::IgnoreAspectRatio);      // 不失真缩放

    // 小车控件
    car = new QLabel(this);
    car->setFixedSize(100,100);
    QPixmapCache::clear();
    car->setPixmap(QPixmap::fromImage(*img));
    car->setVisible(false);

}

void Widget::mousePressEvent(QMouseEvent *event)
{
    if(event->pos().x() < (size().width() - 150) && event->pos().x() > 0
            && event->pos().y() < size().height() && event->pos().y() > 0)
    // 框定合适的绘制范围（区域）
    {
        p[n] = event->pos();
        n++;
        part++;
    }
    if(n >= 2)
        ui->draw_pushButton->setEnabled(true);      // 允许绘制曲线
    update();
}

void Widget::paintEvent(QPaintEvent *)
{
    QPainter paint(&pix);
    QPainter painter(this);
    paint.setRenderHint(QPainter::Antialiasing);    // 反走样功能开启

    // 设置控制点及其连线
    if(state == START && n != 0)
    {
        if(n == 1)
        {
            paint.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap));  // 黑色画控制点
            paint.drawEllipse(p[0],2,2);
        }
        else
        {
            paint.setPen(QPen(QColor(10,250,250), 0.5, Qt::SolidLine, Qt::RoundCap));   // 淡蓝色画模拟直线
            paint.drawLine(p[n-2], p[n-1]);
            paint.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap));
            paint.drawEllipse(p[n-1], 2, 2);
        }
    }
    else if(state == DRAW)
    {   // 绘制曲线————插值点之间用直线相连
        for(int i = 0; i < part * grain; i++)
        {
            paint.setPen(QPen(QColor(250, 0, 0), 1, Qt::SolidLine, Qt::RoundCap)); // 红色画样条曲线
            paint.drawLine(mSpline->spline[i], mSpline->spline[i+1]);
        }
    }
    else if(state == POINT)
    {   // 显示插值点
        for(int i = 0; i < part * grain; i++)
        {
            paint.setBrush(QColor(10, 200, 10)); // 绿色画插值点
            paint.drawEllipse(mSpline->spline[i], 1, 1);
        }
    }
    painter.drawPixmap(0, 0, pix);
}

void Widget::draw()
{
    state = DRAW;   // 绘制曲线模式
    grain = ui->grain_spinBox->value();
    tension = ui->tension_doubleSpinBox->value();
    if(n > 1)
    {
        // 生成Cardinal曲线
        mSpline = new Spline(p, n, grain, tension);

        // 允许显示插值点和播放动画
        ui->point_pushButton->setEnabled(true);
        ui->play_pushButton->setEnabled(true);

        update();
    }
}

void Widget::clear()
{
    // 全部初始化
    state = START;
    n = 0;
    part = -1;
    grain = 0;
    tension = 0;

    pix.fill(Qt::white);

    ui->draw_pushButton->setEnabled(false);
    ui->point_pushButton->setEnabled(false);
    ui->play_pushButton->setEnabled(false);
    ui->pause_pushButton->setEnabled(false);
    ui->speed_horizontalSlider->setValue(7500);
    ui->grain_spinBox->setValue(5);
    ui->tension_doubleSpinBox->setValue(0);

    car->setVisible(false);
    update();
}

void Widget::show_point()
{
    if(state != POINT)
    {
        state = POINT;  // 显示插值点模式
    }
    update();
}

void Widget::play()
{
    state = PLAY;       // 动画播放模式
    grain = ui->grain_spinBox->value();
    tension = ui->tension_doubleSpinBox->value();
    speed = 15000 - ui->speed_horizontalSlider->value();

    ui->pause_pushButton->setText(QString::fromUtf8("暂停"));
    ui->pause_pushButton->setEnabled(true);     // 允许暂停

    grain_total = part * grain;
    timer->setInterval(speed / grain_total);
    double u = 1.0f / grain_total;

    // 设置动画时长，初始帧，关键帧，结束帧
    // 动画的帧沿着插值点分布即可
    ani = new QPropertyAnimation(car, "pos");
    ani->setDuration(speed);
    ani->setStartValue(QPoint(mSpline->spline[0].x() - 40, mSpline->spline[0].y() - 75));
    for(int i = 1; i < grain_total; i++)
    {
        ani->setKeyValueAt(u*i, QPoint(mSpline->spline[i].x() - 40, mSpline->spline[i].y() - 75));
    }
    ani->setEndValue(QPoint(mSpline->spline[grain_total].x() - 40, mSpline->spline[grain_total].y() - 75));

    timer->start();
    update();

}

void Widget::pause_resume()
{
    if(state == PLAY)       // 播放模式——暂停
    {
        ani->pause();
        state = PAUSE;
        ui->pause_pushButton->setText(QString::fromUtf8("继续"));
    }
    else if(state == PAUSE) // 暂停模式——恢复播放
    {
        ani->resume();
        state = PLAY;
        ui->pause_pushButton->setText(QString::fromUtf8("暂停"));
    }

}

// 动画过程控制
// 作为槽函数传递给计时器timer
void Widget::ani_control()
{
    int t = ani->currentTime();
    if(t == 0)
        ani->start();
    if(t > 0)
    {
        int i = round(t / speed * grain_total);
        // 计算斜率和角度
        // 分别带入插值点的纵横坐标之差，得到tan，反求切线角度
        // float atan2(float y, float x)
        // 该函数可以对任何象限的角度求解
        if(i == 0)
            angle = atan(tension*(2*mSpline->spline[1].y() - mSpline->spline[0].y() - mSpline->spline[2].y())/
                    (2*mSpline->spline[1].x() - mSpline->spline[0].x() - mSpline->spline[2].x()))/ PI * 180;
        else if(i == grain_total)
            angle = atan(tension*(2*mSpline->spline[n-1].y() - mSpline->spline[n].y() - mSpline->spline[n-2].y())/
                    (2*mSpline->spline[n-1].x() - mSpline->spline[n].x() - mSpline->spline[n-2].x()))/ PI * 180;
        else
            angle = atan(tension*(mSpline->spline[i+1].y() - mSpline->spline[i-1].y())/
                    (mSpline->spline[i+1].x() - mSpline->spline[i-1].x()))/ PI * 180;

        QMatrix trans;
        trans.rotate(angle);

        // 更新小车图片
        QPixmapCache::clear();
        car->setPixmap(QPixmap::fromImage(*img).transformed(trans, Qt::SmoothTransformation));
        car->setVisible(true);
    }
    if(t >= speed - 150)
    {
        car->setPixmap(QPixmap::fromImage(*img));
        timer->stop();
        ani->stop();
        ui->pause_pushButton->setText(QString::fromUtf8("暂停"));
        ui->pause_pushButton->setEnabled(false);
    }
}

Widget::~Widget()
{
    delete ui;
}

