#include <bfio/Parser/Parser.hpp>

namespace bfio {

Parser::Parser(SourceFile const& source) : source(source), position{0, 0} {
    parse();
}
    
char Parser::current() const {
    return source.char_at(position);
}

void Parser::next() {
    position.character++;
    if (position.character >= source.line_size(position.line)) {
        position.line++;
        position.character = 0;
    }
}

bool Parser::is_eof() const {
    if (position.line == source.line_count() - 1) {
        return position.character >= source.line_size(position.line);
    }
    return position.line >= source.line_count();
}

void Parser::create_token(char c) {
    auto type = tokenType_of(c);
    if (type == TokenType::UNKNOWN) {
        errors.push_back({ParserError::Type::UNKNOWN_CHARACTER, position});
        return;
    }
    tokens.push_back({c, type, position});
}

TokenType Parser::tokenType_of(char c) const {
    switch(c) {
        case '+': return TokenType::INCR;
        case '-': return TokenType::DECR;
        case '<': return TokenType::PTR_LEFT;
        case '>': return TokenType::PTR_RIGHT;
        case '[': return TokenType::BEGIN_LOOP;
        case ']': return TokenType::END_LOOP;
        case '.': return TokenType::OUTPUT;
        case ',': return TokenType::INPUT;
        default: return TokenType::UNKNOWN;
    }
}

void Parser::pass_comments_and_spaces() {
    char c = current();
    while(c == ' ' || c == '\r' || c == '\t' || c == '#') {
        // '#' is the comment
        if (c == '#') {
            position.line++;
            position.character = 0;
        } else {
            next();
        }

        if (is_eof())
            break;
        c = current();
    }
}

void Parser::parse() {
    while(!is_eof()) {
        pass_comments_and_spaces();
        create_token(current());
        next();
    }
}

std::vector<Token> Parser::get_tokens() const {
    return tokens;
}

std::vector<ParserError> Parser::get_errors() const {
    return errors;
}

}