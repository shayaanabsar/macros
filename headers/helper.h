std::vector<std::string> getMatches(std::string s, std::regex reg) {

    std::vector<std::string> matches;
    
    auto begin = std::sregex_iterator(s.begin(), s.end(), reg);
    auto end = std::sregex_iterator();

    for (std::sregex_iterator i = begin; i != end; ++i) {
        std::smatch match = *i;
        matches.push_back(match.str());
    }
    return matches;
}

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
