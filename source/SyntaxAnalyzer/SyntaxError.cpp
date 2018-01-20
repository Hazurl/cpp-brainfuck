#include <bfio/SyntaxAnalyzer/SyntaxError.hpp>

namespace bfio {

std::ostream& SyntaxError::dump(std::ostream& os, SourceFile const& source) const {
    switch(type) {
        case SyntaxError::Type::NO_END_OF_LOOP:
            os << "No end of loop found at " << token.location.line + 1 << ":" << token.location.character << '\n';
        break;
        case SyntaxError::Type::NO_START_OF_LOOP:
            os << "No start of loop found at " << token.location.line + 1 << ":" << token.location.character << '\n';
        break;
    }

    return os;
}

}