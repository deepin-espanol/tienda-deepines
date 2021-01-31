#ifndef SCREENSHOTWIDGET_H
#define SCREENSHOTWIDGET_H

#include <QWidget>
#include <QImage>
#include <QPixmap>
#include <QPicture>
#include <QUrl>
#include <qnetworkreply.h>

namespace Ui {
class ScreenShotWidget;
}

/**
 * @brief Download and show the image specified
 */
class ScreenShotWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ScreenShotWidget(QWidget *parent = nullptr);
    ~ScreenShotWidget();

public Q_SLOTS:
    void downloadFinished(QNetworkReply *);
    void load(QUrl *);

private:
    Ui::ScreenShotWidget *ui;
};

#endif // SCREENSHOTWIDGET_H
