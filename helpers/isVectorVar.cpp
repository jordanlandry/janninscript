#include <vector>
#include <string>


bool isVectorVar(std::vector<std::string> varNames, std::string name) {
    for (int i = 0; i < varNames.size(); i++) {
        if (name == varNames[i]) return true;
    }
    return false;
}