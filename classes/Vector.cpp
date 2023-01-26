class Vector {
public:
    std::vector<int> value;

    int len() {
        return value.size();
    }

    bool includes(int x) {
        for (int i = 0; i < value.size(); i++) {
            if (value[i] == x) return true;
        }

        return false;
    }
};