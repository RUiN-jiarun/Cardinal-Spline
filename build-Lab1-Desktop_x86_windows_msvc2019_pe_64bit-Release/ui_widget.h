/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QLabel *label;
    QLabel *label_2;
    QDoubleSpinBox *tension_doubleSpinBox;
    QSpinBox *grain_spinBox;
    QPushButton *draw_pushButton;
    QPushButton *clear_pushButton;
    QPushButton *point_pushButton;
    QLabel *label_3;
    QSlider *speed_horizontalSlider;
    QPushButton *play_pushButton;
    QPushButton *pause_pushButton;
    QLabel *label_4;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(782, 603);
        label = new QLabel(Widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(570, 10, 121, 21));
        label_2 = new QLabel(Widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(580, 60, 111, 16));
        tension_doubleSpinBox = new QDoubleSpinBox(Widget);
        tension_doubleSpinBox->setObjectName(QString::fromUtf8("tension_doubleSpinBox"));
        tension_doubleSpinBox->setGeometry(QRect(700, 10, 70, 22));
        tension_doubleSpinBox->setMaximum(1.000000000000000);
        tension_doubleSpinBox->setSingleStep(0.100000000000000);
        grain_spinBox = new QSpinBox(Widget);
        grain_spinBox->setObjectName(QString::fromUtf8("grain_spinBox"));
        grain_spinBox->setGeometry(QRect(700, 60, 71, 21));
        grain_spinBox->setMinimum(5);
        grain_spinBox->setMaximum(50);
        draw_pushButton = new QPushButton(Widget);
        draw_pushButton->setObjectName(QString::fromUtf8("draw_pushButton"));
        draw_pushButton->setGeometry(QRect(610, 110, 121, 28));
        clear_pushButton = new QPushButton(Widget);
        clear_pushButton->setObjectName(QString::fromUtf8("clear_pushButton"));
        clear_pushButton->setGeometry(QRect(620, 520, 93, 28));
        point_pushButton = new QPushButton(Widget);
        point_pushButton->setObjectName(QString::fromUtf8("point_pushButton"));
        point_pushButton->setGeometry(QRect(610, 170, 121, 31));
        label_3 = new QLabel(Widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(650, 300, 72, 15));
        speed_horizontalSlider = new QSlider(Widget);
        speed_horizontalSlider->setObjectName(QString::fromUtf8("speed_horizontalSlider"));
        speed_horizontalSlider->setGeometry(QRect(590, 330, 160, 22));
        speed_horizontalSlider->setMinimum(5000);
        speed_horizontalSlider->setMaximum(9999);
        speed_horizontalSlider->setSliderPosition(7500);
        speed_horizontalSlider->setOrientation(Qt::Horizontal);
        play_pushButton = new QPushButton(Widget);
        play_pushButton->setObjectName(QString::fromUtf8("play_pushButton"));
        play_pushButton->setGeometry(QRect(620, 380, 93, 28));
        pause_pushButton = new QPushButton(Widget);
        pause_pushButton->setObjectName(QString::fromUtf8("pause_pushButton"));
        pause_pushButton->setGeometry(QRect(620, 430, 93, 28));
        label_4 = new QLabel(Widget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(600, 570, 161, 16));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        label->setText(QCoreApplication::translate("Widget", "tension [0,1]", nullptr));
        label_2->setText(QCoreApplication::translate("Widget", "grain [5,50]", nullptr));
        draw_pushButton->setText(QCoreApplication::translate("Widget", "\347\273\230\345\210\266\346\240\267\346\235\241\346\233\262\347\272\277", nullptr));
        clear_pushButton->setText(QCoreApplication::translate("Widget", "\346\270\205\347\251\272\347\224\273\345\270\203", nullptr));
        point_pushButton->setText(QCoreApplication::translate("Widget", "\346\230\276\347\244\272\346\217\222\345\200\274\347\202\271", nullptr));
        label_3->setText(QCoreApplication::translate("Widget", "\351\200\237\345\272\246", nullptr));
        play_pushButton->setText(QCoreApplication::translate("Widget", "\346\222\255\346\224\276", nullptr));
        pause_pushButton->setText(QCoreApplication::translate("Widget", "\346\232\202\345\201\234", nullptr));
        label_4->setText(QCoreApplication::translate("Widget", "By:3180105640 \345\210\230\344\275\263\346\266\246", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
