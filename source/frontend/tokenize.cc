#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

namespace liz::frontend {
    std::string purge_comments(std::string code) {
        // std::cout << "Running purge_comments..." << std::endl;

        std::string purged_buffer = "";
        bool add_char = true;
        for(int i = 0; i < code.length(); i++) {
            char char_token = code[i];
            if(char_token == '\n') {
                add_char = true;
            } else if(char_token == '#') {
                add_char = false;
            }

            if(add_char) {
                purged_buffer += char_token;
            }
        }

        return purged_buffer;
    }

    std::vector<std::string> tokenize(std::string code) {
        code = purge_comments(code);

        //std::cout << "Running tokenize..." << std::endl;
        std::vector<std::string> token_list;
        std::string local_token = "";
        
        for(int i = 0; i < code.length(); i++) {
            char char_token = code[i];
            //std::cout << "-> " << i << ". " << char_token << std::endl;
            if(char_token == ' ' || char_token == '\n') {
                if(local_token.length() > 0) {
                    token_list.push_back(local_token);
                }
                local_token = "";
            } else if(char_token == ':') {
                token_list.push_back("typeis");
            } else if(char_token == '{') {
                token_list.push_back("{");
                local_token = "";
            } else if(char_token == '}') {
                token_list.push_back("}");
                local_token = "";
            } else {
                local_token.push_back(char_token);
            }
        }

        token_list.push_back("EOF");
        return token_list;
    };


}
