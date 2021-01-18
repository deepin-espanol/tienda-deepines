#ifndef BOTTOMPACKAGEWIDGETINFORMATIONS_H
#define BOTTOMPACKAGEWIDGETINFORMATIONS_H

#include <QWidget>

struct VirtualField
{
    QWidget *parent = nullptr;
    QString text = "";
    QString descriptor = "";
    int padding = 3;
    QFont *font1 = nullptr;
    QFont *font2 = nullptr;
    bool isEmpty = true;

    const QSize paintingSize();
    const QSize reducedPaintingSize();
    int reducedWidth();
    int width();
    void generatePainting(QPainter &p, QPoint sourcePoint, bool reduced = false);
};

class BottomPackageWidgetInformations : public QWidget
{
    Q_OBJECT
public:
    explicit BottomPackageWidgetInformations(QWidget *parent = nullptr);

    QFont headerFont();
    QFont dataFont();
    int spcaingMargin = 5;

public Q_SLOTS:
    void setHeaders(QList<QString> h);
    void setData(QList<QString> d);
    void setDataFont(QFont f);
    void setHeaderFont(QFont f);
    void clear();

protected:
    void paintEvent(QPaintEvent *e) override;
    void resizeEvent(QResizeEvent *e) override;

private:
    QFont m_headerFont;
    QFont m_dataFont;
    QList<VirtualField> fields;
    bool useCompacted = false;
};

#endif // BOTTOMPACKAGEWIDGETINFORMATIONS_H
