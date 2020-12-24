#ifndef DATAFIELDS_H
#define DATAFIELDS_H

#include <QTabBar>

class DataFields : public QTabBar
{
    Q_OBJECT
public:
    explicit DataFields(QWidget *parent = nullptr);
    ~DataFields();

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
