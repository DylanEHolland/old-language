#include <string>

namespace liz::frontend {
    void tokenize(std::string code);
    std::string purge_comments(std::string code);
}