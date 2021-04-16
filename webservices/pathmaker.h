#ifndef PATHMAKER_H
#define PATHMAKER_H

#include <QString>

enum ImageType {
    Banner,
    Cover,
    Icon,
    Screenshot
};

class PathMaker
{
public:
    PathMaker();

    /**
     * @brief getUrl
     * @param pkgName Name of the package you want
     * @param type The type of image (Banner, Screenshot...)
     * @param pos For screenshot, the first, second one (...)
     * @return The URL of the image
     */
    static QString getUrl(QString pkgName, ImageType type, int pos = 0);
};

#endif // PATHMAKER_H
