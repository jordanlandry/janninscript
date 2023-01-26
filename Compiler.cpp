#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "helpers/skipSpaces.cpp"
#include "classes/Vector.cpp"

void compile(std::string path);

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
    std::ifstream vectorFile;

    build.open("build.cpp", std::ios::app);
    vectorFile.open("./classes/Vector.cpp");

    std::string line;
    while (std::getline(vectorFile, line)) {
        build << line << std::endl;
    }
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
        
        addToMain("\t" + varName + ".value = {");
        while (words[j] != "]") {
            j = skipSpaces(words, j + 1);
            if (words[j] != "]") addToMain(words[j]);
        }

        addToMain("};\n\t");
    }

    else {
        std::string varValue = words[j];
        std::string varType = "int";
        addToMain(varType + " " + varName + " = " + varValue + ";\n");

        addToMain("\n");
    }

    i += (j - i) + 1;

    return i;
}


// Read file line by line and write to build
void readFile(std::string path) {
    std::vector<std::string> variableNames;

    std::ifstream file;
    file.open(path);

    std::string line;
    std::vector<std::string> words;
    while (std::getline(file, line)) {
        // Split line into words
        std::string word = "";
        for (char x : line) {
            if (x == ' ' || x == ';' || x == '{' || x == '}' || x == '(' || x == ')' || x == '\n' || x == '[' || x == ']' || x == ',') {
                if (word != "") {
                    words.push_back(word);
                    word = "";
                }

                std::string s(1, x);
                words.push_back(s);
            }
            else if (x == '.') {
                words.push_back(word);
                word = ".";
            }
            
            else word = word + x;
        }
    }

    // Go through words and write to build
    for (int i = 0; i < words.size(); i++) {
        std::string word = words[i];

        if (word == "var") i = handleAddVar(words, i);
        else if (word == ";") {
            addToMain(";\n\t");
        }

        else addToMain(word);
    }
}

void compile(std::string path) {
    clearBuild();

    includeToBuild();
    
    std::vector<std::string> parameters;
    parameters.push_back("std::string");
    parameters.push_back("int");
    // addPrintFunction(parameters);

    addPrintFunction();
    addClasses();

    addMainFunction();
    readFile(path);
    endMainFunction();

    // Turn the file into c++ code

}



