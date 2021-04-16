#include "utils.h"

QStringList transformToURLs(QString entry)
{
    entry.chop(1);
    entry.remove(0, 1);
    return entry.split("|");
}
