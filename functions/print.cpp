void print() {
    std::cout << "\n";
}

template<typename First, typename ... Strings>
void print(First arg, const Strings&... rest) {
    std::cout << std::boolalpha << arg  << " ";
    print(rest...);
}
