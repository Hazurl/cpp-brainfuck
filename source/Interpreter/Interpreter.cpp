#include <bfio/Interpreter/Interpreter.hpp>

#include <algorithm>
#include <iostream>

namespace bfio {

Interpreter::Interpreter(std::vector<Command> const& commands) 
    : commands(commands), program_pointer(0), cursor(0), preload_input("") {
    std::fill(std::begin(data), std::end(data), 0);
}

void Interpreter::load_input(std::string input) {
    std::reverse(std::begin(input), std::end(input));
    preload_input += input;
}

void Interpreter::run() {
    while(program_pointer < commands.size()) {
        auto cmd = commands[program_pointer];
        program_pointer++;
        switch(cmd.type) {
            case Command::Type::PTR_MOVE:
                cursor += cmd.offset;
                while (cursor >= SIZE) cursor -= SIZE; 
                while (cursor < 0) cursor += SIZE; 
                break;
            case Command::Type::VALUE_ADD:
                data[cursor] += cmd.value;
                break;
            case Command::Type::VALUE_SET:
                data[cursor] = cmd.value;
                break;
            case Command::Type::BRANCH_NOT_0:
                if (data[cursor] != 0) {
                    program_pointer += cmd.offset;
                }
                break;
            case Command::Type::BRANCH_0:
                if (data[cursor] == 0) {
                    program_pointer += cmd.offset;
                }
                break;
            case Command::Type::INPUT:
                if (preload_input == "") {
                    std::cin >> preload_input;
                    std::reverse(std::begin(preload_input), std::end(preload_input));
                }
                data[cursor] = preload_input.back();
                preload_input.pop_back();
                break;
            case Command::Type::OUTPUT:
                std::cout << static_cast<char>(data[cursor]);
                break;
        }
    }
}

}