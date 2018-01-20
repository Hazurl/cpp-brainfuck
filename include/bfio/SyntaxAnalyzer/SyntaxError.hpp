#pragma once

#include <bfio/Token/Token.hpp>
#include <bfio/SourceFile/SourceFile.hpp>

#include <iostream>

namespace bfio {

class SyntaxError {

public:

    enum class Type {
        NO_END_OF_LOOP,
        NO_START_OF_LOOP
    };

    Type type;
    Token token;

    std::ostream& dump(std::ostream& os, SourceFile const& source) const;

};

}