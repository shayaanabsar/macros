std::string getText(std::string filename) {
    std::string text, currLine;
      
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        std::cout << "File '" << filename << "' not found.\n";
        return "";
    }
      
    while (getline(file, currLine)) {
      text += currLine + '\n';
    }
    
    file.close();
    
    return text;
}

