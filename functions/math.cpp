// Values
const double PI = 3.14159265358979323846;
const double E = 2.71828182845904523536;

// Rounding
int floor(double x) {
    return (int) x;
}

int ceil(double x) {
    if (x - (int) x == 0) return (int) x;
    else return (int) x + 1;
}

int round(double x) {
    if (x - (int) x >= 0.5) return (int) x + 1;
    else return (int) x;
}

double round(double x, int decimals) {
    double multiplier = 1;
    for (int i = 0; i < decimals; i++) multiplier *= 10;
    return round(x * multiplier) / multiplier;
}

// Other math functions
double abs(double x) {
    return x < 0 ? -x : x;
}

double square(double x) {
    return x * x;
}

double pow(double x, double y) {
    double result = 1;
    for (int i = 0; i < y; i++) {
        result *= x;
    }
    return result;
}

double log(double x) {
    return log(x);
}

