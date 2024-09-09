int factorial(int n) {
    if (n <= 1) {
        return 1;
    } else {
        return n * factorial(n - 1);
    }
}

int main() {
    int i = 1;
    while (i <= 5) {
        println_int(factorial(i));
        i = i + 1;
    }
    return 0;
}
