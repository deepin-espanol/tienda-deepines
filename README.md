<center><img src="https://raw.githubusercontent.com/deepin-espanol/tienda-deepines/main/deepines.svg"></center>

## Tienda Deepines
Deepines Store (Tienda Deepines) written in C++ with Qt, and Dtk.

### Build dependencies
* libqapt-dev
* libdebconf-kde-dev
* libkf5kio-dev

# KF5 compilation errors
Many people have an inclusion error in KIOCore headers, we too:
```
/usr/include/KF5/KIOCore/kio/global.h:21:10: fatal error: kiocore_export.h: No such file or directory
 #include "kiocore_export.h"
```
This is an inclusion error due to the directory where kiocore_export.h and global.h are located, in Debian (<10).
To fix that, in global.h, replace:
```
#include "kiocore_export.h"
```
With:
```
#include <KF5/KIOCore/kiocore_export.h>
```
But notice that it can happen IN MULTIPLE FILES.


For the inclusion of kcoreaddons_export.h in KJob:
```
#include <KJob>
```
Changed to:
```
#include <KF5/KCoreAddons/KJob>
```
