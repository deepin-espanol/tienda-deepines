#ifndef DATAFIELDS_H
#define DATAFIELDS_H

#include <QTabBar>

/**
 * @brief Show APT BKD data about the PKG in the UI
 */
class DataFields : public QTabBar
{
    Q_OBJECT
public:
    explicit DataFields(QWidget *parent = nullptr);
    ~DataFields();

    QList<QString> headers();
    QList<QString> data();

public Q_SLOTS:
    void setData(QList<QString>);
    void setHeaders(QList<QString>);
    void clear();

protected:
    void updateLabelData();

private:
    QList<QString> m_heads;
    QList<QString> m_data;
};

#endif // DATAFIELDS_H
