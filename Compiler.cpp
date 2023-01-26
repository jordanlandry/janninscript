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

void addFunctions() {
    std::ofstream build;
    std::ifstream readFile;

    build.open("build.cpp", std::ios::app);
    std::vector<std::string> files = {"print", "math"};
    for (int i = 0; i < files.size(); i++) {
        readFile.open("functions/" + files[i] + ".cpp");
        std::string line;
        while (getline(readFile, line)) {
            build << line << std::endl;
        }
        readFile.close();
    }


    // printFile.open("./functions/print.cpp");

    // std::string line;
    // while (std::getline(printFile, line)) {
    //     build << line << std::endl;
    // }
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
void addToBuild(std::string word) {
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
    addToBuild("\n\t");

    int j = i + 1;
    j = skipSpaces(words, j);
    std::string varName = words[j];

    j = skipSpaces(words, j + 1);
    j = skipCertain(words, j, "=");
    j = skipSpaces(words, j + 1);

    // Handle arrays as vectors
    if (words[j] == "[") {
        addToBuild("Vector " + varName + ";\n");

        vectorVariableNames.push_back(varName);
        
        addToBuild("\t" + varName + ".value = {");
        while (words[j] != "]") {
            j = skipSpaces(words, j + 1);
            if (words[j] != "]") {
                addToBuild(words[j]);
            }
        }

        addToBuild("};\n\t");
    }

    // Not an array
    else {
        std::string varValue = words[j];
        std::string varType = figureOutType(varValue);
        if (varType == "int" || varType == "float" || varType == "double") {
            addToBuild("double " + varName + "=" + varValue );
        } 
    }

    i += (j - i);

    return i;
}



int skipToEndOfFunction(std::vector<std::string> words, int i) {
    int j = i;
    int bracketCount = 0;
    int bracketsStarted = false;

    while (j < words.size()) {
        if (words[j] == "{") {
            bracketCount++;
            bracketsStarted = true;
        }
        if (words[j] == "}") bracketCount--;
        if (bracketsStarted && bracketCount == 0) return j;

        j++;
    }
    
    return j;
}

int skipToNextFunction(std::vector<std::string> words, int i) {
    int j = i;
    while (j < words.size()) {
        if (words[j] == "fn") return j;
        j++;
    }
    return j;
}

int handleAddFn(std::vector<std::string> words, int i) {

    addToBuild("auto ");
    i = skipSpaces(words, i + 1);
    addToBuild(words[i] + " = []");

    i = skipSpaces(words, i + 1);

    // Add parameters
    addToBuild("(");

    i = skipSpaces(words, i + 1);
    if (words[i] == ")") addToBuild(")");

    else {
        // addToBuild("double " + words[i]);
        // i = skipSpaces(words, i + 1);

        // addToBuild(",");
        // i = skipSpaces(words, i + 1);

        // addToBuild("double " + words[i]);
        // i = skipSpaces(words, i + 1);

        // std::cout << words[i] << std::endl;
        // addToBuild(")");


        while (words[i] != ")") {
            addToBuild("double " + words[i]);
            i = skipSpaces(words, i + 1);

            if (words[i] == ")") {
                addToBuild(")");
                break;
            }

            addToBuild(",");
            i = skipSpaces(words, i + 1);
        }
    }

    // Add function body
    addToBuild("\n");

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
            if (x == ' ' || x == ';' || x == '{' || x == '}' || x == '(' ||  x == ')' || x == '\n' || x == '[' || x == ']' || x == ',' || x == '+' || x == '-' || x == '*' || x == '/' || x == '=') {
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
        else if (word == ";") addToBuild(";\n\t");
        else if (word == "{") addToBuild("{\n\t");
        else if (word == "}") addToBuild("};\n\t");
        else if (word == "fn") i = handleAddFn(words, i);

        else if (addDotValue) addToBuild(word + ".value");
        else if (word != "fn") addToBuild(word);
    }
}

void compile(std::string path) {
    clearBuild();

    includeToBuild();
    addClasses();

    addFunctions();


    addMainFunction();
    readFile(path);
    endMainFunction();
}