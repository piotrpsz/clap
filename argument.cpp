#include "argument.h"

std::ostream& operator<<(std::ostream& s, Arg const& arg) noexcept {
    s << arg.as_str();
    return s;
}

