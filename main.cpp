#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include <string>
#include "headers/macro.h"
#include "headers/file.h"

int main(int argc, char* argv[]) {
    
    std::string newFileName;
    std::string text;
    
    if (argc != 2 && argc != 4) {
        std::cout << "Usage: ./main input_file\n";
        return 0;
    }
    
    text = getText(argv[1]);
    
    if (text == "") {
        return 0; // Exit Programme if getText returns empty string which indicates the file doesn't exist
    }
    
    text = replaceShorthands(text,  getMacros(text));
    text = std::regex_replace(text, std::regex("#define .+ .+"), "");
    
    rewriteFile(argv[1], text);
}
