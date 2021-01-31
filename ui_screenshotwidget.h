/********************************************************************************
** Form generated from reading UI file 'screenshotwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCREENSHOTWIDGET_H
#define UI_SCREENSHOTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ScreenShotWidget
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;

    void setupUi(QWidget *ScreenShotWidget)
    {
        if (ScreenShotWidget->objectName().isEmpty())
            ScreenShotWidget->setObjectName(QStringLiteral("ScreenShotWidget"));
        ScreenShotWidget->resize(586, 300);
        ScreenShotWidget->setMinimumSize(QSize(0, 290));
        verticalLayout = new QVBoxLayout(ScreenShotWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(ScreenShotWidget);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setPointSize(20);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);


        retranslateUi(ScreenShotWidget);

        QMetaObject::connectSlotsByName(ScreenShotWidget);
    } // setupUi

    void retranslateUi(QWidget *ScreenShotWidget)
    {
        ScreenShotWidget->setWindowTitle(QApplication::translate("ScreenShotWidget", "Form", nullptr));
        label->setText(QApplication::translate("ScreenShotWidget", "Downloading the image...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ScreenShotWidget: public Ui_ScreenShotWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCREENSHOTWIDGET_H
