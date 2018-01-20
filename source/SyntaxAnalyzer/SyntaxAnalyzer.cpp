#include <bfio/SyntaxAnalyzer/SyntaxAnalyzer.hpp>

namespace bfio {

SyntaxAnalyzer::SyntaxAnalyzer(std::vector<Token> const& tokens) : tokens(tokens), position(0) {
    analyze();
}

std::vector<Command> SyntaxAnalyzer::get_commands() const {
    return commands;
}

std::vector<SyntaxError> SyntaxAnalyzer::get_errors() const {
    return errors;
}

Token SyntaxAnalyzer::current() const {
    return tokens[position];
}

void SyntaxAnalyzer::next() {
    position++;
}

bool SyntaxAnalyzer::is_end() const {
    return position >= tokens.size();
}

std::optional<unsigned int> SyntaxAnalyzer::get_begin_loop() const {
    int scope = 1;
    int pos = position - 1;
    for(; scope > 0 && pos >= 0; pos--) {
        auto token = tokens[pos];
        if (token.type == TokenType::BEGIN_LOOP) scope--;
        if (token.type == TokenType::END_LOOP) scope++;
    }
    return scope == 0 ? std::optional<unsigned int>{pos} : std::nullopt;
}

std::optional<unsigned int> SyntaxAnalyzer::get_end_loop() const {
    int scope = 1;
    unsigned int pos = position + 1;
    for(; scope > 0 and pos < tokens.size(); pos++) {
        auto token = tokens[pos];
        if (token.type == TokenType::BEGIN_LOOP) scope++;
        if (token.type == TokenType::END_LOOP) scope--;
    }
    return scope == 0 ? std::optional<unsigned int>{pos} : std::nullopt;
}

void SyntaxAnalyzer::analyze() {
    while(!is_end()) {
        auto token = current();
        Command cmd;
        switch(token.type) {
            case TokenType::PTR_LEFT:
                cmd.type = Command::Type::PTR_MOVE;
                cmd.offset = -1;
                commands.push_back(cmd);
                break;
            case TokenType::PTR_RIGHT:
                cmd.type = Command::Type::PTR_MOVE;
                cmd.offset = 1;
                commands.push_back(cmd);
                break;
            case TokenType::INCR:
                cmd.type = Command::Type::VALUE_ADD;
                cmd.value = 1;
                commands.push_back(cmd);
                break;
            case TokenType::DECR:
                cmd.type = Command::Type::VALUE_ADD;
                cmd.value = -1;
                commands.push_back(cmd);
                break;
            case TokenType::INPUT:
                cmd.type = Command::Type::INPUT;
                commands.push_back(cmd);
                break;
            case TokenType::OUTPUT:
                cmd.type = Command::Type::OUTPUT;
                commands.push_back(cmd);
                break;
            case TokenType::BEGIN_LOOP:
            {
                cmd.type = Command::Type::BRANCH_NOT_0;
                std::optional<unsigned int> end = get_end_loop();
                if (!end.has_value()) {
                    errors.push_back({SyntaxError::Type::NO_START_OF_LOOP, token});
                    return;
                }
                cmd.offset = end.value() - position;
                commands.push_back(cmd);
                break;
            }   
            case TokenType::END_LOOP:
            {
                cmd.type = Command::Type::BRANCH_NOT_0;
                std::optional<unsigned int> end = get_begin_loop();
                if (!end.has_value()) {
                    errors.push_back({SyntaxError::Type::NO_END_OF_LOOP, token});
                    return;
                }
                cmd.offset = end.value() - position;
                commands.push_back(cmd);
                break;
            }
            default:
            break;
            
        }
        next();
    }
}

}