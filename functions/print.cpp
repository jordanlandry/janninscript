void print() {
    return;
}

template<typename First, typename ... Strings>
void print(First arg, const Strings&... rest) {
    std::cout << arg  << std::endl;
    print(rest...);
}