#include <bfio/SourceFile/Loader.hpp>

#include <fstream>
#include <iterator>

namespace bfio {

std::string load_file(std::string path) {
    std::ifstream file(path);
    std::string content;

    file.seekg(0, std::ios::end);   
    content.reserve(file.tellg());
    file.seekg(0, std::ios::beg);

    using stream_it = std::istreambuf_iterator<char>;
    content.assign(stream_it(file), stream_it());

    return content;
}

}