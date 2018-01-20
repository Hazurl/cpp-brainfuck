#include <iostream>
#include <string>

#include <bfio/Loader/Loader.hpp>

int main(int argc, char** argv) {

    if(argc < 2) {
        std::cerr << "File required !\n";
        return 1;
    }

    std::string path(argv[1]);
    std::cout << "Opening " << path << "...\n";
    std::cout << "Content: \n" << bfio::load_file(path) << "\n";

    return 0;
}