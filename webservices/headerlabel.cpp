#include "headerlabel.h"

HeaderLabel::HeaderLabel() : LabelAddon()
{
    QFont f = this->font();
    f.setBold(true);
    f.setWeight(10);
    f.setPointSize(20);
    setFont(f);

    setSizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);
}
