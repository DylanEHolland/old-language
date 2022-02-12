#include <liz.h>
#include <frontend/tokenize.h>
#include <frontend/parser.h>

#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include <fstream>

using std::filesystem::exists;
using std::filesystem::file_size;

namespace liz {

    void load_file(char *file_name) {
        if(exists(file_name)) {
            std::ifstream f(file_name, std::ios::in | std::ios::binary);
            const auto sz = file_size(file_name);
            std::string result(sz, '\0');
            f.read(result.data(), sz);

            auto tokens = frontend::tokenize(result);
            auto tree = frontend::parse(tokens);
            std::cout << "\n===\n\n" << frontend::dumpTree(tree);
        }
    }

}

int main(int argc, char **argv) {
    for(int i = 1; i < argc; i++) {
        liz::load_file(argv[i]);
    }
}