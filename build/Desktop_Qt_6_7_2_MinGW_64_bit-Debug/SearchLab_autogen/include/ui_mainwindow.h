/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGraphicsView *graphicsView;
    QCheckBox *walls;
    QCheckBox *same_distance;
    QPushButton *generate_button;
    QPushButton *clear_button;
    QWidget *widget;
    QVBoxLayout *verticalLayout_7;
    QVBoxLayout *verticalLayout;
    QLabel *start_coords_label;
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *start_x_label;
    QSpinBox *start_x;
    QHBoxLayout *horizontalLayout;
    QLabel *start_y_label;
    QSpinBox *start_y;
    QVBoxLayout *verticalLayout_2;
    QLabel *finish_coords_label;
    QHBoxLayout *horizontalLayout_4;
    QHBoxLayout *horizontalLayout_5;
    QLabel *finish_x_label;
    QSpinBox *finish_x;
    QHBoxLayout *horizontalLayout_6;
    QLabel *finish_y_label;
    QSpinBox *finish_y;
    QWidget *widget1;
    QVBoxLayout *verticalLayout_3;
    QLabel *grid_params_label;
    QHBoxLayout *horizontalLayout_18;
    QHBoxLayout *horizontalLayout_13;
    QLabel *grid_width_label;
    QSpinBox *grid_width;
    QHBoxLayout *horizontalLayout_14;
    QLabel *grid_height_label;
    QSpinBox *grid_height;
    QHBoxLayout *horizontalLayout_17;
    QHBoxLayout *horizontalLayout_15;
    QLabel *wall_chance_label;
    QSpinBox *wall_chance;
    QHBoxLayout *horizontalLayout_16;
    QLabel *max_dist_label;
    QSpinBox *max_distance;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1094, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName("graphicsView");
        graphicsView->setGeometry(QRect(500, 40, 421, 411));
        walls = new QCheckBox(centralwidget);
        walls->setObjectName("walls");
        walls->setGeometry(QRect(260, 200, 92, 25));
        QFont font;
        font.setFamilies({QString::fromUtf8("Fixedsys")});
        font.setPointSize(12);
        walls->setFont(font);
        walls->setChecked(true);
        same_distance = new QCheckBox(centralwidget);
        same_distance->setObjectName("same_distance");
        same_distance->setGeometry(QRect(260, 230, 201, 25));
        same_distance->setFont(font);
        same_distance->setChecked(false);
        generate_button = new QPushButton(centralwidget);
        generate_button->setObjectName("generate_button");
        generate_button->setGeometry(QRect(250, 280, 121, 31));
        generate_button->setFont(font);
        clear_button = new QPushButton(centralwidget);
        clear_button->setObjectName("clear_button");
        clear_button->setGeometry(QRect(370, 280, 121, 31));
        clear_button->setFont(font);
        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(10, 180, 234, 133));
        verticalLayout_7 = new QVBoxLayout(widget);
        verticalLayout_7->setObjectName("verticalLayout_7");
        verticalLayout_7->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        start_coords_label = new QLabel(widget);
        start_coords_label->setObjectName("start_coords_label");
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Fixedsys")});
        font1.setPointSize(12);
        font1.setBold(false);
        font1.setItalic(false);
        start_coords_label->setFont(font1);

        verticalLayout->addWidget(start_coords_label);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        start_x_label = new QLabel(widget);
        start_x_label->setObjectName("start_x_label");
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Fixedsys")});
        font2.setPointSize(12);
        font2.setBold(true);
        font2.setItalic(false);
        start_x_label->setFont(font2);

        horizontalLayout_2->addWidget(start_x_label);

        start_x = new QSpinBox(widget);
        start_x->setObjectName("start_x");
        start_x->setFont(font);

        horizontalLayout_2->addWidget(start_x);


        horizontalLayout_3->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        start_y_label = new QLabel(widget);
        start_y_label->setObjectName("start_y_label");
        start_y_label->setFont(font2);

        horizontalLayout->addWidget(start_y_label);

        start_y = new QSpinBox(widget);
        start_y->setObjectName("start_y");
        start_y->setFont(font);

        horizontalLayout->addWidget(start_y);


        horizontalLayout_3->addLayout(horizontalLayout);


        verticalLayout->addLayout(horizontalLayout_3);


        verticalLayout_7->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        finish_coords_label = new QLabel(widget);
        finish_coords_label->setObjectName("finish_coords_label");
        finish_coords_label->setFont(font1);

        verticalLayout_2->addWidget(finish_coords_label);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        finish_x_label = new QLabel(widget);
        finish_x_label->setObjectName("finish_x_label");
        finish_x_label->setFont(font2);

        horizontalLayout_5->addWidget(finish_x_label);

        finish_x = new QSpinBox(widget);
        finish_x->setObjectName("finish_x");
        finish_x->setFont(font);
        finish_x->setValue(1);

        horizontalLayout_5->addWidget(finish_x);


        horizontalLayout_4->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        finish_y_label = new QLabel(widget);
        finish_y_label->setObjectName("finish_y_label");
        finish_y_label->setFont(font2);

        horizontalLayout_6->addWidget(finish_y_label);

        finish_y = new QSpinBox(widget);
        finish_y->setObjectName("finish_y");
        finish_y->setFont(font);
        finish_y->setValue(1);

        horizontalLayout_6->addWidget(finish_y);


        horizontalLayout_4->addLayout(horizontalLayout_6);


        verticalLayout_2->addLayout(horizontalLayout_4);


        verticalLayout_7->addLayout(verticalLayout_2);

        widget1 = new QWidget(centralwidget);
        widget1->setObjectName("widget1");
        widget1->setGeometry(QRect(10, 40, 414, 125));
        verticalLayout_3 = new QVBoxLayout(widget1);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        grid_params_label = new QLabel(widget1);
        grid_params_label->setObjectName("grid_params_label");
        grid_params_label->setFont(font1);
        grid_params_label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_3->addWidget(grid_params_label);

        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setObjectName("horizontalLayout_18");
        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName("horizontalLayout_13");
        grid_width_label = new QLabel(widget1);
        grid_width_label->setObjectName("grid_width_label");
        grid_width_label->setFont(font1);

        horizontalLayout_13->addWidget(grid_width_label);

        grid_width = new QSpinBox(widget1);
        grid_width->setObjectName("grid_width");
        grid_width->setFont(font);
        grid_width->setMinimum(1);
        grid_width->setMaximum(100);
        grid_width->setValue(10);

        horizontalLayout_13->addWidget(grid_width);


        horizontalLayout_18->addLayout(horizontalLayout_13);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName("horizontalLayout_14");
        grid_height_label = new QLabel(widget1);
        grid_height_label->setObjectName("grid_height_label");
        grid_height_label->setFont(font1);

        horizontalLayout_14->addWidget(grid_height_label);

        grid_height = new QSpinBox(widget1);
        grid_height->setObjectName("grid_height");
        grid_height->setFont(font);
        grid_height->setMinimum(1);
        grid_height->setMaximum(100);
        grid_height->setValue(10);

        horizontalLayout_14->addWidget(grid_height);


        horizontalLayout_18->addLayout(horizontalLayout_14);


        verticalLayout_3->addLayout(horizontalLayout_18);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setSpacing(5);
        horizontalLayout_17->setObjectName("horizontalLayout_17");
        horizontalLayout_17->setContentsMargins(-1, 5, -1, 5);
        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setObjectName("horizontalLayout_15");
        wall_chance_label = new QLabel(widget1);
        wall_chance_label->setObjectName("wall_chance_label");
        wall_chance_label->setFont(font1);

        horizontalLayout_15->addWidget(wall_chance_label);

        wall_chance = new QSpinBox(widget1);
        wall_chance->setObjectName("wall_chance");
        wall_chance->setFont(font);
        wall_chance->setMinimum(2);
        wall_chance->setMaximum(5);

        horizontalLayout_15->addWidget(wall_chance);


        horizontalLayout_17->addLayout(horizontalLayout_15);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setObjectName("horizontalLayout_16");
        max_dist_label = new QLabel(widget1);
        max_dist_label->setObjectName("max_dist_label");
        max_dist_label->setFont(font1);

        horizontalLayout_16->addWidget(max_dist_label);

        max_distance = new QSpinBox(widget1);
        max_distance->setObjectName("max_distance");
        max_distance->setFont(font);
        max_distance->setMinimum(1);
        max_distance->setMaximum(15);
        max_distance->setValue(10);

        horizontalLayout_16->addWidget(max_distance);


        horizontalLayout_17->addLayout(horizontalLayout_16);


        verticalLayout_3->addLayout(horizontalLayout_17);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1094, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        walls->setText(QCoreApplication::translate("MainWindow", "\321\201\321\202\321\226\320\275\320\270", nullptr));
        same_distance->setText(QCoreApplication::translate("MainWindow", "\320\276\320\264\320\275\320\260\320\272\320\276\320\262\320\260 \320\262\321\226\320\264\321\201\321\202\320\260\320\275\321\214", nullptr));
        generate_button->setText(QCoreApplication::translate("MainWindow", "\320\227\320\263\320\265\320\275\320\265\321\200\321\203\320\262\320\260\321\202\320\270", nullptr));
        clear_button->setText(QCoreApplication::translate("MainWindow", "\320\236\321\207\320\270\321\201\321\202\320\270\321\202\320\270", nullptr));
        start_coords_label->setText(QCoreApplication::translate("MainWindow", "\320\232\320\276\320\276\321\200\320\264\320\270\320\275\320\260\321\202\320\270 \321\202\320\276\321\207\320\272\320\270 \321\201\321\202\320\260\321\200\321\202\321\203", nullptr));
        start_x_label->setText(QCoreApplication::translate("MainWindow", "x:", nullptr));
        start_y_label->setText(QCoreApplication::translate("MainWindow", "y:", nullptr));
        finish_coords_label->setText(QCoreApplication::translate("MainWindow", "\320\232\320\276\320\276\321\200\320\264\320\270\320\275\320\260\321\202\320\270 \321\202\320\276\321\207\320\272\320\270 \321\204\321\226\320\275\321\226\321\210\321\203", nullptr));
        finish_x_label->setText(QCoreApplication::translate("MainWindow", "x:", nullptr));
        finish_y_label->setText(QCoreApplication::translate("MainWindow", "y:", nullptr));
        grid_params_label->setText(QCoreApplication::translate("MainWindow", "\320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200\320\270 \321\201\321\226\321\202\320\272\320\270", nullptr));
        grid_width_label->setText(QCoreApplication::translate("MainWindow", "\321\210\320\270\321\200\320\270\320\275\320\260:", nullptr));
        grid_height_label->setText(QCoreApplication::translate("MainWindow", "\320\262\320\270\321\201\320\276\321\202\320\260:", nullptr));
        wall_chance_label->setText(QCoreApplication::translate("MainWindow", "\321\201\321\202\321\226\320\275\320\260:", nullptr));
        max_dist_label->setText(QCoreApplication::translate("MainWindow", "\320\274\320\260\320\272\321\201. \320\262\321\226\320\264\321\201\321\202\320\260\320\275\321\214:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
