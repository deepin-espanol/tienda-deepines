#include "filteroptionswidget.h"

#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>

FilterOptionsWidget::FilterOptionsWidget(QWidget *parent) : QWidget(parent)
{
    m_scheme = new PackagesFilterScheme;
    loadUI();
}

FilterOptionsWidget::~FilterOptionsWidget()
{
    this->layout()->~QLayout();
    this->QWidget::~QWidget();
}

void FilterOptionsWidget::loadUI()
{
    QGridLayout *lay = new QGridLayout;

    QLineEdit *version = new QLineEdit();
    QLineEdit *architecture = new QLineEdit();
    QLineEdit *section = new QLineEdit();
    QLineEdit *name = new QLineEdit();
    QLineEdit *state = new QLineEdit();

    QLabel *lab_version = new QLabel(tr("Version"));
    QLabel *lab_architecture = new QLabel(tr("Architecture"));
    QLabel *lab_section = new QLabel(tr("Section"));
    QLabel *lab_name = new QLabel(tr("Package"));
    QLabel *lab_state = new QLabel(tr("State"));

    QCheckBox *box1 = new QCheckBox(tr("Inclusive", "Perform lookups for the package"));

    box1->setChecked(true);

    /*  1      1   1   1
     *  __________________
     * |_____|________|___|
     * |_____|____________|
     * |_____|____________|
     * |_____|____________|
     */

    lay->addWidget(        lab_name, 0, 0, 1, 1);
    lay->addWidget(     lab_version, 1, 0, 1, 1);
    lay->addWidget(     lab_section, 2, 0, 1, 1);
    lay->addWidget(lab_architecture, 3, 0, 1, 1);

        lay->addWidget(        name, 0, 2, 2, 1);
        lay->addWidget(     version, 1, 2, 3, 1);
        lay->addWidget(     section, 2, 2, 3, 1);
        lay->addWidget(architecture, 3, 2, 3, 1);

                lay->addWidget(box1, 0, 4, 1, 1);

    connect(box1, &QCheckBox::stateChanged, this, [box1, this]() {
        m_scheme->includedString = box1->isChecked();
        Q_EMIT schemeUpdated(*m_scheme);
    });
    connect(version, &QLineEdit::editingFinished, this, [version, this]() {
        m_scheme->version = version->text();
        Q_EMIT schemeUpdated(*m_scheme);
    });
    connect(name, &QLineEdit::editingFinished, this, [name, this]() {
        m_scheme->name = name->text();
        Q_EMIT schemeUpdated(*m_scheme);
    });
    connect(architecture, &QLineEdit::editingFinished, this, [architecture, this]() {
        m_scheme->arch = architecture->text();
        Q_EMIT schemeUpdated(*m_scheme);
    });
    connect(section, &QLineEdit::editingFinished, this, [section, this]() {
        m_scheme->section = section->text();
        Q_EMIT schemeUpdated(*m_scheme);
    });

    this->setLayout(lay);
}
