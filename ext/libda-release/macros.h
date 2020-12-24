#ifndef MACROS_H
#define MACROS_H

#define PRAGMA_STR1(x)  #x
#define PRAGMA_STR2(x)  PRAGMA_STR1 (x)
#define NOTE(x)  message (__FILE__ "(" PRAGMA_STR2(__LINE__) ") : -NOTE- " #x)
#define NOTE_wARG(x,y)  message(__FILE__ "(" PRAGMA_STR2(__LINE__) ") : -NOTE- " #x PRAGMA_STR2(y))

#define EL_IF(x) else if (x)

#ifndef DQT_NO_KEYWORDS
#define elif(x) EL_IF(x)
#endif

#endif // MACROS_H
