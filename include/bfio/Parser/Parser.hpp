#pragma once

#include <string>
#include <vector>

#include <bfio/Token/Token.hpp>
#include <bfio/SourceFile/SourceFile.hpp>
#include <bfio/Parser/ParserError.hpp>

namespace bfio {

class Parser {
public:

    Parser(SourceFile const& source);

    std::vector<Token> get_tokens() const;
    std::vector<ParserError> get_errors() const;

private:

    SourceFile source;
    Location position;

    std::vector<Token> tokens;
    std::vector<ParserError> errors;

    void parse();

    void pass_comments_and_spaces();
    bool is_eof() const;

    char current() const;
    void next();

    void create_token(char c);
    TokenType tokenType_of(char c) const;

};

}