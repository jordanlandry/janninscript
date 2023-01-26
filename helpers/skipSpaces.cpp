#include <vector>
#include <string>

int skipSpaces(std::vector<std::string> words, int i) {
    while (words[i] == " " || words[i] == "\n") i++;
    return i;
}

int skipCertain(std::vector<std::string> words, int i, std::string toSkip) {
    while (words[i] != toSkip) i++;
    return i;
}

int skipTo(std::vector<std::string> words, int i, std::string toSkip) {
    while (words[i] != toSkip) i++;
    return i + 1;
}

// Look for ; before =
bool isUndefined(std::vector<std::string> words, int i) {
    while (words[i] != ";") {
        if (words[i] == "=") return false;
        i++;
    }

    return true;
}