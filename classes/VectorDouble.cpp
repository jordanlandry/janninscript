class VectorDouble {
public:
    std::vector<double> value;

    void clear() {
        value.clear();
    }

    void push(double x) {
        value.push_back(x);
    }

    int len() {
        return value.size();
    }

    void removeIndex(int i) {
        value.erase(value.begin() + i);
    }

    void removeAll(bool x) {
        for (int i = 0; i < value.size(); i++) {
            if (value[i] == x) {
                value.erase(value.begin() + i);
                i--;
            }
        }
    }

    void removeFirst(bool x) {
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