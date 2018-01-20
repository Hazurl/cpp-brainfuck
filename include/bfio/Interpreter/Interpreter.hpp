#pragma once

#include <bfio/SyntaxAnalyzer/Command.hpp>

#include <vector>
#include <array>
#include <string>

namespace bfio {

class Interpreter {
public:

    static constexpr unsigned int SIZE = 2000;

    Interpreter(std::vector<Command> const& commands);

    void load_input(std::string input);
    void run();

private:

    std::vector<Command> commands;
    std::string preload_input;

    unsigned int program_pointer;

    int cursor;
    std::array<int, SIZE> data;

};

}