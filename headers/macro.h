class Macro {
    public:
        std::string shorthand;
        std::string longhand;
};

std::string escape_special(std::string str) {
    std::string newStr = "";
    std::string special_characters = "\\^$.|?*+()[{";

    for (int i = 0; i < str.length(); i++) {
        for (int j = 0; j < special_characters.length(); j++) {
            if (str[i] == special_characters[j]) {
                newStr += '\\';
                break;
            } 
        }
        newStr += str[i];
    }
    
    return newStr;
}

std::string replaceDoubleSpaces(std::string str) {
    return std::regex_replace(str, std::regex(" {2,}"), " "); // replace multi-spaces with single spaces
}

Macro makeMacroObject(std::string macroDefinition) {
    int sp1 = macroDefinition.find(' ');
    int sp2 = macroDefinition.find(' ', sp1 + 1);
    
    std::string shorthand = macroDefinition.substr(sp1 + 1, sp2 - sp1 - 1); // exclusive substring from 1st space to 2nd space
    std::string longhand = macroDefinition.substr(sp2 + 1, std::string::npos); // exclusive substring from 2nd space to end
    
    // Create macro Object
    
    Macro macro;
    
    macro.shorthand = escape_special(shorthand);
    macro.longhand = longhand;
    
    return macro;
}

std::vector<Macro> getMacros(std::string text) {
    // Returns a vector of all of the macro definitions
    
    std::vector<Macro> macros;
    std::regex macroRegex("#define +.+ +.+");

    auto begin = std::sregex_iterator(text.begin(), text.end(), macroRegex);
    auto end = std::sregex_iterator();

    for (std::sregex_iterator i = begin; i != end; ++i) {
        std::smatch match = *i;
        std::string macroDefinition = replaceDoubleSpaces(match.str());
        
        macros.push_back(makeMacroObject(macroDefinition));
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

