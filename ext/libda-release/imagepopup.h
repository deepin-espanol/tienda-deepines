#ifndef IMAGEPOPUP_H
#define IMAGEPOPUP_H

#include "libda_global.h"
#include <DLabel>
#include <DDialogCloseButton>
#include <QDialog>

DWIDGET_USE_NAMESPACE

LDA_BEGIN_NAMESPACE

/**
 * @brief ImagePopup class is like the image viewer of Deepin Manual
 */
class LIBDA_SHARED_EXPORT ImagePopup : public QDialog
{
    Q_OBJECT
public:
    explicit ImagePopup(QWidget *parent = nullptr);
    ~ImagePopup() override;

public slots:
    /**
     * @brief Open/Show/Popup the image on the screen to let the user see it
     * @param image
     */
    void open(QImage &image);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    void init();

    DLabel *img = nullptr;
    DDialogCloseButton *close;
    QImage data;

    using QDialog::open;
};

LDA_END_NAMESPACE

#endif // IMAGEPOPUP_H
