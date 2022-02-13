#include <frontend/parser.h>

#include <string>
#include <vector>
#include <iostream>

namespace liz::frontend {
    std::string dumpToken(struct node *token, std::string prefix) {
        std::string buffer = "";
        if(token->type == VALUE) {
            buffer = prefix + token->value;
            buffer = buffer + "\n";
        } else if(token->type == STRUCT) {
            buffer = "structure";
            buffer = buffer + "\n";
        } else if(token->type == BLOCK) {
            dumpTree(token->child, prefix);
        }

        return buffer;
    }

    std::string dumpTree(struct node *code_tree, std::string prefix) {
        struct node *head = code_tree;//reverseParsedTree(code_tree);
        std::string output = "";
        while(head->active) {
            output += dumpToken(head, prefix);

            head = head->next;
        }

        return output;
    }

    struct node *duplicateToken(struct node *token) {
        struct node *buffer = new struct node();
        buffer->type = token->type;
        buffer->value = token->value;
        buffer->active = token->active;
        buffer->child = token->child;

        return buffer;
    }

    struct node *parse(std::vector<std::string> tokens) {
        int tokenCount = 0;
        for(std::string str : tokens) {
            if(tokens[tokenCount] == "EOF") break;
            tokenCount++;
        }
        
        auto failed = false;
        struct node *head = new struct node();

        for(int index = 0; index < tokenCount; index++) {
            std::string token = tokens[index];            
            struct node *self = new struct node();
            self->active = true;

            if(token == "{") {
                std::vector<std::string> sub_tokens;
                self->type = BLOCK;
                if(index < tokenCount - 1) {
                    int i = 0;
                    for(i = index + 1; i < tokenCount - 1; i++) {
                        sub_tokens.push_back(tokens[i]);
                    }
                    
                    self->child = parse(sub_tokens);  
                    index += treeSize(self->child);
                } else {
                    std::cout << "Unexpected end of file" << std::endl;
                    exit(-1);
                }
                
            } else if(token == "}") {
                return head;
            } else if(token == "=") {
                self->type = EQUALS;
            } else if(token == "struct") {
                self->type = STRUCT;
            } else {
                self->type = VALUE;
                self->value = token;
            }
            
            
            self->next = head;
            head = self;
        }

        return head;
    }

    struct node *reverseParsedTree(struct node *code_tree) {
        struct node *initialTreeToken = code_tree;
        struct node *normifiedTreeToken = new struct node();

        while(initialTreeToken->active) {
            struct node * token = duplicateToken(initialTreeToken);

            if(!normifiedTreeToken) {
                normifiedTreeToken = token;
                normifiedTreeToken->next = new struct node();
            } else {
                struct node *buffer = token;
                buffer->next = normifiedTreeToken;
                normifiedTreeToken = buffer;
            }
            
            initialTreeToken = initialTreeToken->next;
        }

        return normifiedTreeToken;
    }

    int treeSize(struct node *code_tree) {
        struct node *head = code_tree;
        int count = 0;

        while(head) {
            count++;
            head = head->next;
        }

        return count;
    }
}