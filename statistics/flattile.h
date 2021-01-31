#ifndef FLATTILE_H
#define FLATTILE_H

#include <QWidget>

/**
 * @brief UI Tile with rounded corners
 */
class FlatTile : public QWidget
{
    Q_OBJECT
public:
    explicit FlatTile(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *e) override;
    int borderRadius = 5;
};


class FlatContainer : public QWidget
{
    Q_OBJECT
public:
    explicit FlatContainer(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *e) override;
};

#endif // FLATTILE_H
