#include <bfio/SourceFile/SourceFile.hpp>

namespace bfio {

SourceFile::SourceFile(std::string const& content) {
    std::string line;
    for (auto c : content) {
        if (c == '\n' && !line.empty()) {
            source.push_back(line);
            line = "";
        } else {
            line += c;
        }
    }
    if (!line.empty())
        source.push_back(line);    
}

unsigned int SourceFile::line_count() const {
    return source.size();
}

unsigned int SourceFile::line_size(unsigned int line) const {
    return source[line].size();
}

char SourceFile::char_at(Location const& location) const {
    return source[location.line][location.character];
}

}