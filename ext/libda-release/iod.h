#ifndef IOD_H
#define IOD_H

#include "libda_global.h"
#include <fstream>

namespace iod {
class LIBDA_SHARED_EXPORT IOD
{
public:
    IOD();
    ~IOD();

    static IOD *instance();
    static void setOutputFile(const char *);
    static void output(const char *);
    static void output(void *);
    static void output(const int);

private:
    std::ofstream streaming;
};
}

#endif // IOD_H
