void print() {
    return;
}


template<typename First, typename ... Strings>
void print(First arg, const Strings&... rest) {
    std::cout << std::boolalpha << arg  << std::endl;
    print(rest...);
}
