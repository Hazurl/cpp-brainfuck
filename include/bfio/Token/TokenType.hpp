#pragma once

namespace bfio {

enum class TokenType {

    PTR_LEFT, PTR_RIGHT,
    INCR, DECR,
    BEGIN_LOOP, END_LOOP,
    INPUT, OUTPUT,

    UNKNOWN

};

}