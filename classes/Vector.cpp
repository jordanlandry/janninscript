class Vector {
public:
    std::vector<double> value;

    int len() {
        return value.size();
    }
    
    void push(double x) {
        value.push_back(x);
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



    // Quick sort

    void quickSort(std::vector<double> &v, int start, int end) {
        if (start >= end) return;

        int pivot = v[end];
        int pivotIndex = start;

        for (int i = start; i < end; i++) {
            if (v[i] < pivot) {
                std::swap(v[i], v[pivotIndex]);
                pivotIndex++;
            }
        }

        std::swap(v[pivotIndex], v[end]);

        quickSort(v, start, pivotIndex - 1);
        quickSort(v, pivotIndex + 1, end);
    }
    
    void sort() {
        quickSort(value, 0, value.size() - 1);
    }

    // void reverse() {
    //     std::reverse(value.begin(), value.end());
    // }


    void removeFirst(double x) {
        for (int i = 0; i < value.size(); i++) {
            if (value[i] == x) {
                value.erase(value.begin() + i);
                return;
            }
        }
    }

    void removeAll(double x) {
        for (int i = 0; i < value.size(); i++) {
            if (value[i] == x) {
                value.erase(value.begin() + i);
                i--;
            }
        }
    }

    bool includes(double x) {
        for (int i = 0; i < value.size(); i++) {
            if (value[i] == x) return true;
        }

        return false;
    }
};