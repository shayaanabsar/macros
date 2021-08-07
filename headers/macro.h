#include "helper.h"

class Macro {
    public:
        std::string shorthand;
        std::string longhand;
};

Macro makeMacroObject(std::string macroDefinition, bool isParameterMacro=false) {
    Macro macro;
    macroDefinition = replaceDoubleSpaces(macroDefinition);
    macro.shorthand = escape_special(getMatches(macroDefinition, std::regex("\\b\\w+\\b")).at(1));
    
    int length = std::string ("#define ").length() + macro.shorthand.length();
    
    macro.longhand = macroDefinition.substr(length + 1, std::string::npos);
  
    return macro;
}

std::vector<Macro> getMacros(std::string text) {
    // Returns a vector of all of the macro definitions
    
    std::vector<Macro> macros;
    std::regex macroRegex("#define +[A-Za-z0-9_]+ +.+");

    std::vector<std::string> matches = getMatches(text, macroRegex);
    
    for (int i = 0; i < matches.size(); i++) {
        macros.push_back(makeMacroObject(matches.at(i)));
    }
    
    return macros;
}    


std::string replaceShorthands(std::string text, std::vector<Macro> macros) {
    // Uses regexes to replace the shorthands with the longhands
    
    for (int i = 0; i < macros.size(); i++) {
        std::regex currRegex("\\b" + macros.at(i).shorthand + "\\b");
        
        text = std::regex_replace(text, currRegex, macros.at(i).longhand);
    
    }
    
    return text;
}

