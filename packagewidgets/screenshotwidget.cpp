#include "packagewidgets/screenshotwidget.h"
#include "ui_screenshotwidget.h"

#include <QNetworkAccessManager>

ScreenShotWidget::ScreenShotWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScreenShotWidget)
{
    this->setStyleSheet("background: #00000000;");
    ui->setupUi(this);
}

void ScreenShotWidget::downloadFinished(QNetworkReply *reply)
{
    QPixmap pm;

    if (reply->error() != QNetworkReply::NetworkError::NoError) {
        pm.loadFromData(reply->readAll());
        ui->label->setPixmap(pm.scaledToHeight(ui->label->height(), Qt::FastTransformation));
        setVisible(true);
    } else {
        setVisible(false);
    }
}

void ScreenShotWidget::load(QUrl *path)
{
    QNetworkAccessManager *nam = new QNetworkAccessManager(this);
    connect(nam, &QNetworkAccessManager::finished, this, &ScreenShotWidget::downloadFinished);
    QNetworkRequest request(*path);
    nam->get(request);
}

ScreenShotWidget::~ScreenShotWidget()
{
    delete ui;
}
