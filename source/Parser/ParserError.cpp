#include <bfio/Parser/ParserError.hpp>

namespace bfio {

std::ostream& ParserError::dump(std::ostream& os, SourceFile const& source) const {
    switch(type) {
        case ParserError::Type::UNKNOWN_CHARACTER:
            os << "Unknown character '" << source.char_at(location)
               << "' at " << location.line + 1 << ":" << location.character << '\n';
        break;
    }

    return os;
}

}