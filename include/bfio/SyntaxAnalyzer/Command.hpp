#pragma once

namespace bfio {

class Command {
public:

    enum class Type {
        PTR_MOVE, BRANCH_NOT_0, BRANCH_0,
        VALUE_ADD, VALUE_SET,
        INPUT, OUTPUT
    };

    Type type;

    union {
        int offset;
        int value;
    };
};

}