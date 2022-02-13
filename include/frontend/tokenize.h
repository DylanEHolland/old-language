#include <string>
#include <vector>

namespace liz::frontend {
    std::vector<std::string> tokenize(std::string code);
    std::string purge_comments(std::string code);
}