#pragma once

#include <bfio/Token/Token.hpp>
#include <bfio/SyntaxAnalyzer/Command.hpp>
#include <bfio/SyntaxAnalyzer/SyntaxError.hpp>

#include <vector>
#include <optional>

namespace bfio {

class SyntaxAnalyzer {
public:

    SyntaxAnalyzer(std::vector<Token> const& tokens);

    std::vector<Command> get_commands() const;
    std::vector<SyntaxError> get_errors() const;

private:

    std::vector<Token> tokens;
    std::vector<Command> commands;
    std::vector<SyntaxError> errors;

    unsigned int position;

    Token current() const;
    void next();
    bool is_end() const;

    void analyze();

    std::optional<unsigned int> get_end_loop() const;
    std::optional<unsigned int> get_begin_loop() const;

};

}