#include <iostream>
#include <string>
#include <fstream>
#include <vector>

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

    build << "    return 0;" << std::endl;
    build << "}" << std::endl;
}

// Anything not in a function is added to the main function
void addToMain(std::string word) {
    std::ofstream build;
    build.open("build.cpp", std::ios::app);

    build << " " << word;
    if (word == ";" || word == "}" || word == "{") {
        build << std::endl;
    }
}

// Read file word by word
void readFile(std::string path) {
    std::fstream file;
    std::string word, t, q, filename;

    file.open(path);

    while (file >> word) {
        // Add a new print function with the correct parameters
        addToMain(word);
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

    addMainFunction();
    readFile(path);
    endMainFunction();

    // Turn the file into c++ code

}



