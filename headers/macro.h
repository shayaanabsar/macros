class Macro {
    public:
        std::string shorthand;
        std::string longhand;
};

std::vector<Macro> getMacros(std::string text) {
    std::vector<Macro> macros;
    std::regex macroRegex("#define .+ .+");

    auto begin = std::sregex_iterator(text.begin(), text.end(), macroRegex);
    auto end = std::sregex_iterator();

    for (std::sregex_iterator i = begin; i != end; ++i) {
        std::smatch match = *i;
        std::string s = match.str();
        
        std::cout << s.find(' ') << s.find(' ', s.find(' ') + 1)<<'\n';
        
        int sp1 = s.find(' ');
        int sp2 = s.find(' ', s.find(' ') + 1);
        
        std::string shorthand = s.substr(sp1 + 1, sp2 - sp1 - 1); // exclusive substring from 1st space to 2nd space
        std::string longhand = s.substr(sp2 + 1, std::string::npos); // exclusive substring from 2nd space to end
        
        // Create new macro and add to vector
        
        Macro curr_macro;
        
        curr_macro.shorthand = shorthand;
        curr_macro.longhand = longhand;
        
        macros.push_back(curr_macro);
    }
    
    return macros;
}

/*
std::string replaceShorthands(std::string text, vector<Macros>macros) {
    
}
*/