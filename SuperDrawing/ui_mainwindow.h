/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include <my_widget.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QSpinBox *spinBox;
    QPushButton *pushButton_Load;
    QTableWidget *tableWidget;
    my_widget *widget;
    QPushButton *pushButton_draw;
    QPushButton *pushButton_clear;
    QPushButton *pushButton_Save_as;
    QPushButton *pushButton_Save;
    QPushButton *pushButton_SaveWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1386, 1060);
        QFont font;
        font.setPointSize(18);
        MainWindow->setFont(font);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName("centralWidget");
        label = new QLabel(centralWidget);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 13, 281, 31));
        QFont font1;
        font1.setPointSize(15);
        label->setFont(font1);
        spinBox = new QSpinBox(centralWidget);
        spinBox->setObjectName("spinBox");
        spinBox->setGeometry(QRect(300, 13, 91, 41));
        QFont font2;
        font2.setPointSize(13);
        spinBox->setFont(font2);
        spinBox->setMaximum(20);
        pushButton_Load = new QPushButton(centralWidget);
        pushButton_Load->setObjectName("pushButton_Load");
        pushButton_Load->setGeometry(QRect(1220, 150, 151, 41));
        pushButton_Load->setFont(font2);
        tableWidget = new QTableWidget(centralWidget);
        if (tableWidget->columnCount() < 8)
            tableWidget->setColumnCount(8);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(20, 70, 1191, 361));
        QFont font3;
        font3.setPointSize(9);
        tableWidget->setFont(font3);
        tableWidget->setColumnCount(8);
        tableWidget->horizontalHeader()->setCascadingSectionResizes(false);
        tableWidget->horizontalHeader()->setMinimumSectionSize(46);
        tableWidget->horizontalHeader()->setDefaultSectionSize(146);
        tableWidget->verticalHeader()->setDefaultSectionSize(40);
        tableWidget->verticalHeader()->setProperty("showSortIndicator", QVariant(false));
        widget = new my_widget(centralWidget);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(20, 440, 1200, 500));
        pushButton_draw = new QPushButton(centralWidget);
        pushButton_draw->setObjectName("pushButton_draw");
        pushButton_draw->setGeometry(QRect(410, 10, 141, 41));
        pushButton_draw->setFont(font2);
        pushButton_clear = new QPushButton(centralWidget);
        pushButton_clear->setObjectName("pushButton_clear");
        pushButton_clear->setGeometry(QRect(560, 10, 141, 41));
        pushButton_clear->setFont(font2);
        pushButton_Save_as = new QPushButton(centralWidget);
        pushButton_Save_as->setObjectName("pushButton_Save_as");
        pushButton_Save_as->setGeometry(QRect(1220, 110, 151, 41));
        pushButton_Save_as->setFont(font2);
        pushButton_Save = new QPushButton(centralWidget);
        pushButton_Save->setObjectName("pushButton_Save");
        pushButton_Save->setGeometry(QRect(1220, 70, 151, 41));
        pushButton_Save->setFont(font2);
        pushButton_SaveWidget = new QPushButton(centralWidget);
        pushButton_SaveWidget->setObjectName("pushButton_SaveWidget");
        pushButton_SaveWidget->setGeometry(QRect(1130, 0, 241, 51));
        pushButton_SaveWidget->setFont(font2);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 1386, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName("mainToolBar");
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName("statusBar");
        MainWindow->setStatusBar(statusBar);
        QWidget::setTabOrder(spinBox, tableWidget);
        QWidget::setTabOrder(tableWidget, pushButton_draw);
        QWidget::setTabOrder(pushButton_draw, pushButton_clear);
        QWidget::setTabOrder(pushButton_clear, pushButton_Save);
        QWidget::setTabOrder(pushButton_Save, pushButton_Save_as);
        QWidget::setTabOrder(pushButton_Save_as, pushButton_Load);
        QWidget::setTabOrder(pushButton_Load, pushButton_SaveWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276 \321\215\320\273\320\265\320\274\320\265\320\275\321\202\320\276\320\262:", nullptr));
        pushButton_Load->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214", nullptr));
        pushButton_draw->setText(QCoreApplication::translate("MainWindow", "\320\240\320\270\321\201\320\276\320\262\320\260\321\202\321\214", nullptr));
        pushButton_clear->setText(QCoreApplication::translate("MainWindow", "\320\236\321\207\320\270\321\201\321\202\320\272\320\260", nullptr));
        pushButton_Save_as->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\272\320\260\320\272", nullptr));
        pushButton_Save->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", nullptr));
        pushButton_SaveWidget->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \321\200\320\270\321\201\321\203\320\275\320\276\320\272 \320\272\320\260\320\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
