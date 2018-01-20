#include <iostream>
#include <string>

#include <bfio/SourceFile/Loader.hpp>
#include <bfio/Parser/Parser.hpp>

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
    std::cout << "0\n";
    auto src0 = bfio::SourceFile("+-<>[].,");
    bfio::Parser parser0(src0);
    for(auto const& error : parser0.get_errors()) {
        error.dump(std::cout, src0);
    }
    std::cout << "1\n";
    auto src1 = bfio::SourceFile("+-<>[]., # comment \n # another one \n d");
    bfio::Parser parser1(src1);
    for(auto const& error : parser1.get_errors()) {
        error.dump(std::cout, src1);
    }
    std::cout << "2\n";
    auto src2 = bfio::SourceFile("+-<>[].,@");
    bfio::Parser parser2(src2);
    for(auto const& error : parser2.get_errors()) {
        error.dump(std::cout, src2);
    }

    return 0;
}