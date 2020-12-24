#include "datafields.h"

#include <iostream>
#include <QResizeEvent>
#include <DThemeManager>
#include <DGuiApplicationHelper>

DataFields::DataFields(QWidget *parent) : QTabBar(parent) {}

DataFields::~DataFields()
{
    m_heads.~QList();
    m_data.~QList();
    this->QTabBar::~QTabBar();
}

void DataFields::setData(QList<QString> l)
{
    m_data = l;
    updateLabelData();
}

void DataFields::setHeaders(QList<QString> l)
{
    m_heads = l;
    updateLabelData();
}

void DataFields::clear()
{
    while (count() != 0) {
        removeTab(0);
    }
}

void DataFields::updateLabelData()
{
    int max = m_heads.length();
    if (m_heads.length() > m_data.length()) {
        max = m_data.length();
    }

    this->clear();
    int i = 0;
    //Generate and update labels' data
    while (i<max) {
        if (tabButton(i, QTabBar::LeftSide) != nullptr) {
            setTabData(i, m_heads.at(i) + m_data.at(i));
        } else {
            addTab(m_heads.at(i) + m_data.at(i));
        }
        i++;
    }
}
