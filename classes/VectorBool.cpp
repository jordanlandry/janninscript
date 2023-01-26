class VectorBool {
public:
    std::vector<bool> value;

    void clear() {
        value.clear();
    }

    void push(bool x) {
        value.push_back(x);
    }

    int len() {
        return value.size();
    }

    void removeIndex(int i) {
        value.erase(value.begin() + i);
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