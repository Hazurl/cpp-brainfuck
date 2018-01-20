#include <iostream>
#include <string>
#include <optional>

#include <bfio/SourceFile/Loader.hpp>
#include <bfio/Parser/Parser.hpp>
#include <bfio/SyntaxAnalyzer/SyntaxAnalyzer.hpp>

int main(int argc, char** argv) {
/*
    if(argc < 2) {
        std::cerr << "File required !\n";
        return 1;
    }

    std::string path(argv[1]);
    std::cout << "Opening " << path << "...\n";
    std::cout << "Content: \n" << bfio::load_file(path) << "\n";
*/
    std::cout << "Parser : \n";
    auto src = bfio::SourceFile("...[[[][]]]]...");
    bfio::Parser parser(src);
    for(auto const& error : parser.get_errors()) {
        error.dump(std::cout, src);
    }
    
    std::cout << "Analyzer : \n";
    bfio::SyntaxAnalyzer analyzer(parser.get_tokens());
    for(auto const& error : analyzer.get_errors()) {
        error.dump(std::cout, src);
    }

    std::cout << "Commands : \n";
    for(auto const& cmd : analyzer.get_commands()) {
        std::cout << static_cast<int>(cmd.type) << std::endl;
    }

    return 0;
}