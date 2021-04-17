#ifndef COLORMODIFIER_H
#define COLORMODIFIER_H

#include <ostream>
namespace Color {
    enum Code {
        RESET = 0,
        BOLD_BRIGHT = 1,
        UNDERLINE = 4,
        INVERSE = 7,
        BOLD_BRIGHT_OFF = 21,
        UNDERLINE_OFF = 24,
        INVERSE_OFF = 27,

        FG_BLACK = 30,
        FG_RED = 31,
        FG_GREEN = 32,
        FG_YELLOW = 33,
        FG_BLUE = 34,
        FG_MAGENTA = 35,
        FG_CYAN = 36,
        FG_WHITE = 37,
        FG_TRANS = 38,
        FG_DEFAULT  = 39,

        BG_BLACK = 40,
        BG_RED = 41,
        BG_GREEN = 42,
        BG_YELLOW = 43,
        BG_BLUE = 44,
        BG_MAGENTA = 45,
        BG_CYAN = 46,
        BG_WHITE = 47,
        BG_TRANS = 48,
        BG_DEFAULT  = 49
    };

    /**
     * @brief Output this class in a stream to change parameters depending of your combination of Code
     */
    class Modifier {
        Code code;
    public:
        Modifier(Code pCode) : code(pCode) {}
        friend std::ostream&
        operator<<(std::ostream& os, const Modifier& mod) {
            return os << "\033[" << mod.code << "m";
        }
    };
}

#endif // COLORMODIFIER_H
