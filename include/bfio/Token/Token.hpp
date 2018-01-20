#pragma once

#include <bfio/Token/TokenType.hpp>
#include <bfio/SourceFile/Location.hpp>

namespace bfio {

class Token {
public:

    char source;
    TokenType type;
    Location location;

};

}