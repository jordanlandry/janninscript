#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "helpers/skipSpaces.cpp"
#include "helpers/isVectorVar.cpp"

void compile(std::string path);

std::vector<std::string> vectorVariableNames;
int main() {
    compile("./build.jannin");
    return 0;
}

void clearBuild() {
    std::ofstream buildFile;
    buildFile.open("./build.cpp");
    buildFile << "";
    buildFile.close();    
}

void includeToBuild() {
    // Write to build.cpp
    std::ofstream build;
    build.open("build.cpp", std::ios::app);
    build << "#include <iostream>" << std::endl;
    build << "#include <string>" << std::endl;
    build << "#include <fstream>" << std::endl;
    build << "#include <vector>" << std::endl;
}

void addPrintFunction() {
    std::ofstream build;
    std::ifstream printFile;

    build.open("build.cpp", std::ios::app);
    printFile.open("./functions/print.cpp");

    std::string line;
    while (std::getline(printFile, line)) {
        build << line << std::endl;
    }
}

void addMainFunction() {
    std::ofstream build;
    build.open("build.cpp", std::ios::app);
    build << "int main() {" << std::endl;
}

void endMainFunction() {
    std::ofstream build;
    build.open("build.cpp", std::ios::app);

    build << "return 0;" << std::endl;
    build << "}" << std::endl;
}

// Anything not in a function is added to the main function
void addToMain(std::string word) {
    std::ofstream build;
    build.open("build.cpp", std::ios::app);

    build << word;
}

void addClasses() {
    std::ofstream build;
    build.open("build.cpp", std::ios::app);

    std::vector<std::string> classes = {"Vector"};
    for (int i = 0; i < classes.size(); i++) {
        std::ifstream classFile;
        classFile.open("./classes/" + classes[i] + ".cpp");

        std::string line;
        while (std::getline(classFile, line)) {
            build << line << std::endl;
        }
    }
}

std::string figureOutType(std::string word) {
    // Return int for now 
    return "int";
}

int handleAddVar(std::vector<std::string> words, int i) {
    addToMain("\n\t");

    int j = i + 1;
    j = skipSpaces(words, j);
    std::string varName = words[j];

    j = skipSpaces(words, j + 1);
    j = skipCertain(words, j, "=");
    j = skipSpaces(words, j + 1);

    // Handle arrays as vectors
    if (words[j] == "[") {
        addToMain("Vector " + varName + ";\n");

        vectorVariableNames.push_back(varName);
        
        addToMain("\t" + varName + ".value = {");
        while (words[j] != "]") {
            j = skipSpaces(words, j + 1);
            if (words[j] != "]") {
                addToMain(words[j]);
            }
        }

        addToMain("};\n\t");
    }

    // Not an array
    else {
        std::string varValue = words[j];
        std::string varType = figureOutType(varValue);
        if (varType == "int" || varType == "float" || varType == "double") {
            addToMain("double " + varName + "=" + varValue + "; ");
        } 
    }

    i += (j - i) + 1;

    return i;
}

// Read file line by line and write to build
void readFile(std::string path) {

    std::ifstream file;
    file.open(path);

    std::string line;
    std::vector<std::string> words;

    while (std::getline(file, line)) {
        // Split line into words
        std::string word = "";
        for (char x : line) {
            if (x == ' ' || x == ';' || x == '{' || x == '}' || x == '(' || x == ')' || x == '\n' || x == '[' || x == ']' || x == ',' || x == '+' || x == '-' || x == '*' || x == '/' || x == '=') {
                if (word != "") {
                    words.push_back(word);
                    word = "";
                }

                std::string s(1, x);
                words.push_back(s);
            }

            else if (x == '.') {
                words.push_back(word);
                word = "";
                word += x;
            }
            
            else word = word + x;
        }
    }

    // Go through words and write to build
    for (int i = 0; i < words.size(); i++) {
        std::string word = words[i];

        // Add .value because we are using a class
        bool addDotValue = isVectorVar(vectorVariableNames, word) && words[i + 1][0] != '.';

        if (word == "var") i = handleAddVar(words, i);
        else if (addDotValue) addToMain(word + ".value");
        else addToMain(word);
    }
}

void compile(std::string path) {
    clearBuild();

    includeToBuild();

    addPrintFunction();
    addClasses();

    addMainFunction();
    readFile(path);
    endMainFunction();
}