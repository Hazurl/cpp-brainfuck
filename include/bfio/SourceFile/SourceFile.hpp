#pragma once

#include <string>
#include <vector>

#include <bfio/SourceFile/Location.hpp>

namespace bfio {

class SourceFile {
public:

    SourceFile(std::string const& source);

    unsigned int line_count() const;
    unsigned int line_size(unsigned int line) const;

    char char_at(Location const& location) const; // may throw an exception std::out_of_range

private:

    std::vector<std::string> source;

};

}