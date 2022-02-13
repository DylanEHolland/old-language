#pragma once

namespace liz::backend::vm {
    enum instruction {
        PRINT_CHAR,
        PRINT_INT    
    };

    void printChar();
    void printInt();
};