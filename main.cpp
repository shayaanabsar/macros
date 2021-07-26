#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include <string>
#include "headers/macro.h"
#include "headers/file.h"

std::vector<Macro> getMacros(std::string text);

int main(int argc, char* argv[]) {
    
    if (argc != 2 && argc != 4) {
        std::cout << "Usage: ./main input_file [-o output_file]\n";
        return 0;
    }
    
    std::string text;
    
    text = getText(argv[1]);
    
    if (text == "") {
        return 0; // Exit Programme if getText returns empty string which indicates the file doesn't exist
    }
    
    std::vector<Macro> macros = getMacros(text);
    /*
    for (int i = 0; i < macros.size(); i++) {
        std::cout << '"'<< macros.at(i).shorthand <<'"' << ':' << '"'<< macros.at(i).longhand << '"'<< '\n';
    }
    */
}



