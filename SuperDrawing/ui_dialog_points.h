/********************************************************************************
** Form generated from reading UI file 'dialog_points.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_POINTS_H
#define UI_DIALOG_POINTS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog_points
{
public:
    QTableWidget *tableWidget;
    QSpinBox *spinBox;
    QPushButton *pushButton_Ok;
    QPushButton *pushButton_Cancel;
    QLabel *label;

    void setupUi(QDialog *Dialog_points)
    {
        if (Dialog_points->objectName().isEmpty())
            Dialog_points->setObjectName("Dialog_points");
        Dialog_points->resize(685, 396);
        QFont font;
        font.setPointSize(18);
        Dialog_points->setFont(font);
        tableWidget = new QTableWidget(Dialog_points);
        if (tableWidget->columnCount() < 2)
            tableWidget->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        if (tableWidget->rowCount() < 3)
            tableWidget->setRowCount(3);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(20, 10, 281, 341));
        QFont font1;
        font1.setPointSize(12);
        tableWidget->setFont(font1);
        tableWidget->setRowCount(3);
        spinBox = new QSpinBox(Dialog_points);
        spinBox->setObjectName("spinBox");
        spinBox->setGeometry(QRect(550, 20, 101, 41));
        spinBox->setMinimum(3);
        spinBox->setMaximum(20);
        pushButton_Ok = new QPushButton(Dialog_points);
        pushButton_Ok->setObjectName("pushButton_Ok");
        pushButton_Ok->setGeometry(QRect(370, 340, 131, 41));
        pushButton_Cancel = new QPushButton(Dialog_points);
        pushButton_Cancel->setObjectName("pushButton_Cancel");
        pushButton_Cancel->setGeometry(QRect(530, 340, 131, 41));
        label = new QLabel(Dialog_points);
        label->setObjectName("label");
        label->setGeometry(QRect(340, 20, 211, 41));
        QWidget::setTabOrder(spinBox, tableWidget);
        QWidget::setTabOrder(tableWidget, pushButton_Ok);
        QWidget::setTabOrder(pushButton_Ok, pushButton_Cancel);

        retranslateUi(Dialog_points);

        QMetaObject::connectSlotsByName(Dialog_points);
    } // setupUi

    void retranslateUi(QDialog *Dialog_points)
    {
        Dialog_points->setWindowTitle(QCoreApplication::translate("Dialog_points", "Dialog", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("Dialog_points", "X", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("Dialog_points", "Y", nullptr));
        pushButton_Ok->setText(QCoreApplication::translate("Dialog_points", "Ok", nullptr));
        pushButton_Cancel->setText(QCoreApplication::translate("Dialog_points", "\320\236\321\202\320\274\320\265\320\275\320\260", nullptr));
        label->setText(QCoreApplication::translate("Dialog_points", "\320\232\320\276\320\273-\320\262\320\276 \321\202\320\276\321\207\320\265\320\272:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog_points: public Ui_Dialog_points {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_POINTS_H
