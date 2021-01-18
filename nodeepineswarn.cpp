#include "nodeepineswarn.h"

#include <QLabel>
#include <QHBoxLayout>
#include <QPixmap>
#include <QDesktopServices>
#include <QUrl>

NoDeepinesWarn::NoDeepinesWarn() : DDialog() {}

void NoDeepinesWarn::generatePopup()
{
    setTitle(tr("Tienda Deepines Error"));
    setCloseButtonVisible(true);
    setIcon(QIcon::fromTheme("dialog-warning"));

    this->setMaximumWidth(300);

    QWidget *content = new QWidget(this);
    QHBoxLayout *lay = new QHBoxLayout;
    QLabel *icon = new QLabel;
    QLabel *message = new QLabel;

    icon->setFixedSize(60, 60);
    //[TODO] use a "deepines repository" icon
    icon->setPixmap(QIcon::fromTheme("dialog-warning").pixmap(icon->size()));

    message->setWordWrap(true);
    message->setText(tr("Looks like you haven't the Deepin En Español repositories. Some packages in the Selection section or other might be unavailable. You can add manually the repository if you want."));

    lay->addWidget(icon);
    lay->addWidget(message);
    content->setLayout(lay);
    addContent(content);

    int openIt = this->addButton(tr("Tutorial from the web"), true, ButtonType::ButtonRecommend);
    int closeIt = this->addButton(tr("Close"), false, ButtonType::ButtonNormal);

    connect(this, &DDialog::buttonClicked, this, [this, openIt, closeIt](int val) {
        if (val == openIt) {
            this->close();
            QDesktopServices::openUrl(QUrl("https://xn--deepinenespaol-1nb.org/"));
        }  if (val == closeIt) {
            this->close();
        }
    });

    this->exec();
    this->moveToCenter();
}
