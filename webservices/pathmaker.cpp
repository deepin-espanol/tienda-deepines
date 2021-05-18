#include "pathmaker.h"

PathMaker::PathMaker() {}

QString PathMaker::getUrl(QString pkgName, ImageType type, int pos)
{
    if (type == ImageType::Cover) {
        if (pkgName == "atom") {
            return "file:///home/nicolas/Pictures/bcfigdjeidinjdigfonocnhbamldpc.png";
        } else if (pkgName == "auryo"){
            return "file:///home/nicolas/Pictures/departure_by_auroralion_d9czi3p-pre.jpg";
        } else {
            return "file:///home/nicolas/Pictures/flower_blooming_bud_130161_2560x1440.jpg";
        }
    }
    return "";
}
