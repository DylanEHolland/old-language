#pragma once
#include <string>
#include <vector>
#include <iostream>

namespace liz::frontend {
    enum node_type {
        BLOCK,
        EQUALS,
        VARIABLE_NAME,
        VALUE,
        ADD,
        SUB,
        MUL,
        DIV,
        STRUCT
    };

    struct node {
        node() {
            // std::cout << "Allocating..." << std::endl;
            this->active = false;
        }

        enum node_type type;
        std::string value;
        struct node *next;
        struct node *child;
        bool active;
    };

    std::string dumpToken(struct node token, std::string prefix = "");
    std::string dumpTree(struct node *head, std::string prefix = "");
    struct node *duplicateToken(struct node *token);
    struct node *parse(std::vector<std::string> tokens);
    struct node *reverseParsedTree(struct node *code_tree);
    int treeSize(struct node *code_tree);
}