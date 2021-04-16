#include "spacers.h"

VSpacer::VSpacer() : QSpacerItem(0, 0, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding), AbstractElement() {}
HSpacer::HSpacer() : QSpacerItem(0, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum), AbstractElement() {}
