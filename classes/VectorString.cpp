class VectorString {
public:
    std::vector<std::string> value;

    int len() {
        return value.size();
    }

    void push(std::string x) {
        value.push_back(x);
    }

    void removeIndex(int i) {
        value.erase(value.begin() + i);
    }

    void clear() {
        value.clear();
    }

    void removeAll(std::string x) {
        for (int i = 0; i < value.size(); i++) {
            if (value[i] == x) {
                value.erase(value.begin() + i);
                i--;
            }
        }
    }

    void removeFirst(std::string x) {
        for (int i = 0; i < value.size(); i++) {
            if (value[i] == x) {
                value.erase(value.begin() + i);
                return;
            }
        }
    }

    void print() {
        std::cout << "[";
        for (int i = 0; i < value.size(); i++) {
            std::cout << value[i];
            if (i != value.size() - 1) std::cout << ", ";
        }
        std::cout << "]" << std::endl;
    }

};