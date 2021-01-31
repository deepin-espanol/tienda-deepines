#ifndef SPLITTEDBUTTON_H
#define SPLITTEDBUTTON_H

#include <DButtonBox>
#include <DPushButton>
#include <QMenu>

/**
 * @brief Between QPushButton and QToolButton
 */
class SplittedButton : public Dtk::Widget::DButtonBox
{
    Q_OBJECT
public:
    explicit SplittedButton(QWidget *parent = nullptr);
    explicit SplittedButton(QAction *mainAction, QWidget *parent = nullptr);
    explicit SplittedButton(QAction *mainAction, QMenu *optionalMenu, QWidget *parent = nullptr);

public Q_SLOTS:
    void setDefaultAction(QAction *action);
    void setOptionalMenu(QMenu *menu);
    void setMainButtonEnabled(bool enable = true);
    void setOptionalButtonEnabled(bool enable = true);
    void updateMainButton();

protected:
    void resizeEvent(QResizeEvent *e) override;

private Q_SLOTS:
    void popupMenu();

private:
    QMenu *m_menu = nullptr;
    QAction *m_act = nullptr;
    Dtk::Widget::DButtonBoxButton *mainBtn =nullptr;
    Dtk::Widget::DButtonBoxButton *optionalBtn = nullptr;
};

#endif // SPLITTEDBUTTON_H
