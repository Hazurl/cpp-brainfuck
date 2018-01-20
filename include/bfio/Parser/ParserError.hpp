#pragma once

#include <bfio/SourceFile/Location.hpp>
#include <bfio/SourceFile/SourceFile.hpp>
#include <iostream>

namespace bfio {

class ParserError {
public:

    enum class Type {
        UNKNOWN_CHARACTER
    };

    Type type;
    Location location;

    std::ostream& dump(std::ostream& os, SourceFile const& source) const;

};


}