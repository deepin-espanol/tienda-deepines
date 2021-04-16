#ifndef HEADERBAR_H
#define HEADERBAR_H

#include <QWidget>

/**
 * @brief Banner of the PKG, shows icon, name (...)
 */
class HeaderBar : public QWidget
{
    Q_OBJECT
public:
    explicit HeaderBar(QWidget *parent = nullptr);

    void load(QUrl url);
    void setWidget(QWidget *w);
    void setName(QString name);
    void checkSizes();

protected:
    void paintEvent(QPaintEvent *e) override;
    void resizeEvent(QResizeEvent *e) override;

private:
    QPixmap img;
    QString m_name = "Hi!";
    QWidget *m = nullptr;
};

#endif // HEADERBAR_H
