/********************************************************************************
** Form generated from reading UI file 'dialog_style.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_STYLE_H
#define UI_DIALOG_STYLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_Dialog_style
{
public:
    QLabel *label_style;
    QPushButton *pushButton_Ok;
    QPushButton *pushButton_Cancel;
    QLabel *label_width;
    QComboBox *comboBox_line;
    QLabel *label_style_2;
    QComboBox *comboBox_brush;
    QSpinBox *spinBox_Width;
    QPushButton *pushButton_colorLine;
    QPushButton *pushButton_colorBrush;
    QLabel *label_line;
    QLabel *label_brush;

    void setupUi(QDialog *Dialog_style)
    {
        if (Dialog_style->objectName().isEmpty())
            Dialog_style->setObjectName("Dialog_style");
        Dialog_style->resize(848, 478);
        QFont font;
        font.setPointSize(18);
        Dialog_style->setFont(font);
        label_style = new QLabel(Dialog_style);
        label_style->setObjectName("label_style");
        label_style->setGeometry(QRect(20, 40, 141, 41));
        QFont font1;
        font1.setPointSize(12);
        label_style->setFont(font1);
        pushButton_Ok = new QPushButton(Dialog_style);
        pushButton_Ok->setObjectName("pushButton_Ok");
        pushButton_Ok->setGeometry(QRect(540, 410, 121, 31));
        QFont font2;
        font2.setPointSize(15);
        pushButton_Ok->setFont(font2);
        pushButton_Cancel = new QPushButton(Dialog_style);
        pushButton_Cancel->setObjectName("pushButton_Cancel");
        pushButton_Cancel->setGeometry(QRect(690, 410, 121, 31));
        pushButton_Cancel->setFont(font2);
        label_width = new QLabel(Dialog_style);
        label_width->setObjectName("label_width");
        label_width->setGeometry(QRect(20, 140, 151, 41));
        label_width->setFont(font1);
        comboBox_line = new QComboBox(Dialog_style);
        comboBox_line->addItem(QString());
        comboBox_line->addItem(QString());
        comboBox_line->addItem(QString());
        comboBox_line->addItem(QString());
        comboBox_line->addItem(QString());
        comboBox_line->addItem(QString());
        comboBox_line->setObjectName("comboBox_line");
        comboBox_line->setGeometry(QRect(160, 40, 271, 41));
        comboBox_line->setFont(font);
        label_style_2 = new QLabel(Dialog_style);
        label_style_2->setObjectName("label_style_2");
        label_style_2->setGeometry(QRect(20, 200, 141, 41));
        label_style_2->setFont(font1);
        comboBox_brush = new QComboBox(Dialog_style);
        comboBox_brush->addItem(QString());
        comboBox_brush->addItem(QString());
        comboBox_brush->addItem(QString());
        comboBox_brush->addItem(QString());
        comboBox_brush->addItem(QString());
        comboBox_brush->addItem(QString());
        comboBox_brush->addItem(QString());
        comboBox_brush->addItem(QString());
        comboBox_brush->addItem(QString());
        comboBox_brush->addItem(QString());
        comboBox_brush->addItem(QString());
        comboBox_brush->addItem(QString());
        comboBox_brush->addItem(QString());
        comboBox_brush->addItem(QString());
        comboBox_brush->addItem(QString());
        comboBox_brush->setObjectName("comboBox_brush");
        comboBox_brush->setGeometry(QRect(160, 200, 381, 41));
        comboBox_brush->setFont(font);
        spinBox_Width = new QSpinBox(Dialog_style);
        spinBox_Width->setObjectName("spinBox_Width");
        spinBox_Width->setGeometry(QRect(170, 140, 71, 41));
        spinBox_Width->setMinimum(1);
        spinBox_Width->setMaximum(20);
        pushButton_colorLine = new QPushButton(Dialog_style);
        pushButton_colorLine->setObjectName("pushButton_colorLine");
        pushButton_colorLine->setGeometry(QRect(20, 90, 201, 41));
        pushButton_colorBrush = new QPushButton(Dialog_style);
        pushButton_colorBrush->setObjectName("pushButton_colorBrush");
        pushButton_colorBrush->setGeometry(QRect(20, 250, 201, 41));
        label_line = new QLabel(Dialog_style);
        label_line->setObjectName("label_line");
        label_line->setGeometry(QRect(440, 40, 351, 121));
        label_brush = new QLabel(Dialog_style);
        label_brush->setObjectName("label_brush");
        label_brush->setGeometry(QRect(560, 180, 351, 111));
        QWidget::setTabOrder(comboBox_line, comboBox_brush);
        QWidget::setTabOrder(comboBox_brush, pushButton_colorLine);
        QWidget::setTabOrder(pushButton_colorLine, spinBox_Width);
        QWidget::setTabOrder(spinBox_Width, pushButton_colorBrush);
        QWidget::setTabOrder(pushButton_colorBrush, pushButton_Ok);
        QWidget::setTabOrder(pushButton_Ok, pushButton_Cancel);

        retranslateUi(Dialog_style);

        QMetaObject::connectSlotsByName(Dialog_style);
    } // setupUi

    void retranslateUi(QDialog *Dialog_style)
    {
        Dialog_style->setWindowTitle(QCoreApplication::translate("Dialog_style", "Dialog", nullptr));
        label_style->setText(QCoreApplication::translate("Dialog_style", "\320\241\321\202\320\270\320\273\321\214 \320\273\320\270\320\275\320\270\320\270", nullptr));
        pushButton_Ok->setText(QCoreApplication::translate("Dialog_style", "\320\236\320\232", nullptr));
        pushButton_Cancel->setText(QCoreApplication::translate("Dialog_style", "\320\236\321\202\320\274\320\265\320\275\320\260", nullptr));
        label_width->setText(QCoreApplication::translate("Dialog_style", "\320\242\320\276\320\273\321\211\320\270\320\275\320\260 \320\273\320\270\320\275\320\270\320\270", nullptr));
        comboBox_line->setItemText(0, QCoreApplication::translate("Dialog_style", "\320\235\320\265\321\202 \321\200\321\203\321\207\320\272\320\270", nullptr));
        comboBox_line->setItemText(1, QCoreApplication::translate("Dialog_style", "\320\241\320\277\320\273\320\276\321\210\320\275\320\260\321\217", nullptr));
        comboBox_line->setItemText(2, QCoreApplication::translate("Dialog_style", "\320\237\321\203\320\275\320\272\321\202\320\270\321\200\320\275\320\260\321\217", nullptr));
        comboBox_line->setItemText(3, QCoreApplication::translate("Dialog_style", "\320\242\320\276\321\207\320\265\321\207\320\275\320\260\321\217", nullptr));
        comboBox_line->setItemText(4, QCoreApplication::translate("Dialog_style", "\320\242\320\270\321\200\320\265-\321\202\320\276\321\207\320\272\320\260", nullptr));
        comboBox_line->setItemText(5, QCoreApplication::translate("Dialog_style", "\320\242\320\270\321\200\320\265-\321\202\320\276\321\207\320\272\320\260-\321\202\320\276\321\207\320\272\320\260", nullptr));

        label_style_2->setText(QCoreApplication::translate("Dialog_style", "\320\241\321\202\320\270\320\273\321\214 \320\267\320\260\320\273\320\270\320\262\320\272\320\270", nullptr));
        comboBox_brush->setItemText(0, QCoreApplication::translate("Dialog_style", "\320\235\320\265\321\202 \320\267\320\260\320\273\320\270\320\262\320\272\320\270", nullptr));
        comboBox_brush->setItemText(1, QCoreApplication::translate("Dialog_style", "\320\241\320\277\320\273\320\276\321\210\320\275\320\260\321\217", nullptr));
        comboBox_brush->setItemText(2, QCoreApplication::translate("Dialog_style", "\320\242\320\276\321\207\320\265\321\207\320\275\320\260\321\217 (\320\277\320\273\320\276\321\202\320\275\320\276\321\201\321\202\321\214 1)", nullptr));
        comboBox_brush->setItemText(3, QCoreApplication::translate("Dialog_style", "\320\242\320\276\321\207\320\265\321\207\320\275\320\260\321\217 (\320\277\320\273\320\276\321\202\320\275\320\276\321\201\321\202\321\214 2)", nullptr));
        comboBox_brush->setItemText(4, QCoreApplication::translate("Dialog_style", "\320\242\320\276\321\207\320\265\321\207\320\275\320\260\321\217 (\320\277\320\273\320\276\321\202\320\275\320\276\321\201\321\202\321\214 3)", nullptr));
        comboBox_brush->setItemText(5, QCoreApplication::translate("Dialog_style", "\320\242\320\276\321\207\320\265\321\207\320\275\320\260\321\217 (\320\277\320\273\320\276\321\202\320\275\320\276\321\201\321\202\321\214 4)", nullptr));
        comboBox_brush->setItemText(6, QCoreApplication::translate("Dialog_style", "\320\242\320\276\321\207\320\265\321\207\320\275\320\260\321\217 (\320\277\320\273\320\276\321\202\320\275\320\276\321\201\321\202\321\214 5)", nullptr));
        comboBox_brush->setItemText(7, QCoreApplication::translate("Dialog_style", "\320\242\320\276\321\207\320\265\321\207\320\275\320\260\321\217 (\320\277\320\273\320\276\321\202\320\275\320\276\321\201\321\202\321\214 6)", nullptr));
        comboBox_brush->setItemText(8, QCoreApplication::translate("Dialog_style", "\320\242\320\276\321\207\320\265\321\207\320\275\320\260\321\217 (\320\277\320\273\320\276\321\202\320\275\320\276\321\201\321\202\321\214 7)", nullptr));
        comboBox_brush->setItemText(9, QCoreApplication::translate("Dialog_style", "\320\223\320\276\321\200\320\270\320\267\320\276\320\275\321\202\320\260\320\273\321\214\320\275\320\260\321\217", nullptr));
        comboBox_brush->setItemText(10, QCoreApplication::translate("Dialog_style", "\320\222\320\265\321\200\321\202\320\270\320\272\320\260\320\273\321\214\320\275\320\260\321\217", nullptr));
        comboBox_brush->setItemText(11, QCoreApplication::translate("Dialog_style", "\320\222 \320\272\320\273\320\265\321\202\320\276\321\207\320\272\321\203", nullptr));
        comboBox_brush->setItemText(12, QCoreApplication::translate("Dialog_style", "\320\224\320\270\320\260\320\263\320\276\320\275\320\260\320\273\321\214\320\275\320\260\321\217(\320\262\320\277\321\200\320\260\320\262\320\276)", nullptr));
        comboBox_brush->setItemText(13, QCoreApplication::translate("Dialog_style", "\320\224\320\270\320\260\320\263\320\276\320\275\320\260\320\273\321\214\320\275\320\260\321\217(\320\262\320\273\320\265\320\262\320\276)", nullptr));
        comboBox_brush->setItemText(14, QCoreApplication::translate("Dialog_style", "\320\224\320\270\320\260\320\263\320\276\320\275\320\260\320\273\321\214\320\275\320\276-\320\272\320\273\320\265\321\202\320\276\321\207\320\275\320\260\321\217", nullptr));

        pushButton_colorLine->setText(QCoreApplication::translate("Dialog_style", "\320\246\320\262\320\265\321\202 \320\273\320\270\320\275\320\270\320\270", nullptr));
        pushButton_colorBrush->setText(QCoreApplication::translate("Dialog_style", "\320\246\320\262\320\265\321\202 \320\267\320\260\320\273\320\270\320\262\320\272\320\270", nullptr));
        label_line->setText(QString());
        label_brush->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Dialog_style: public Ui_Dialog_style {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_STYLE_H
