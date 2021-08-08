#include "helper.h"

class Macro {
    public:
        std::string shorthand;
        std::string longhand;
        std::vector<std::string> parameters;
};

Macro makeMacroObject(std::string macroDefinition, bool isParameterMacro=false) {
    Macro macro;
    macroDefinition = replaceDoubleSpaces(macroDefinition);
    macro.shorthand = escape_special(getMatches(macroDefinition, std::regex("\\b\\w+\\b")).at(1));

    int length = std::string ("#define ").length() + macro.shorthand.length();

    if (isParameterMacro) {
        std::string parameterStr = getMatches(macroDefinition, std::regex("\\(\\s*\\S+\\s*(?:,\\s*\\S+)*\\)")).at(0);
        macro.parameters = getMatches(parameterStr, std::regex("\\b\\w+\\b"));

        length += parameterStr.length();
    }

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

    std::regex parameterMacroRegex("#define +[A-Za-z0-9_]+\\(\\s*\\S+\\s*(?:,\\s*\\S+)*\\) +.+");

    matches = getMatches(text, parameterMacroRegex);

    for (int i = 0; i < matches.size(); i++) {
        macros.push_back(makeMacroObject(matches.at(i), true));
    }

    return macros;
}

std::string replaceParameters(std::string s, Macro macro) {
    std::string parameterStr = getMatches(s, std::regex("\\(\\s*\\S+\\s*(?:,\\s*\\S+)*\\)")).at(0);
    std::vector<std::string> parameterValues = getMatches(parameterStr, std::regex("\\b\\w+\\b"));

    std::string newStr = macro.longhand;

    for (int i = 0; i < macro.parameters.size(); i++) {
        newStr = std::regex_replace(newStr, std::regex("\\b" + macro.parameters.at(i) + "\\b"), parameterValues.at(i));
    }
    
    return newStr;
}

std::string replaceShorthands(std::string text, std::vector<Macro> macros) {
    // Uses regexes to replace the shorthands with the longhands

    for (int i = 0; i < macros.size(); i++) {
        std::regex currRegex("\\b" + macros.at(i).shorthand + "\\b");
        
        if (macros.at(i).parameters.size() != 0) {
            currRegex = ("\\b" + macros.at(i).shorthand + "\\b\\(\\s*\\S+\\s*(?:,\\s*\\S+)*\\)");
            std::vector<std::string> matches = getMatches(text, currRegex);
            
            for (int j = 0; j < matches.size(); j++) {
                std::string replaceString = replaceParameters(matches.at(j), macros.at(i));
                text = std::regex_replace(text, currRegex, replaceString, std::regex_constants::format_first_only);
            }
            
        } else {
            text = std::regex_replace(text, currRegex, macros.at(i).longhand);
        }
    }

    return text;
}
