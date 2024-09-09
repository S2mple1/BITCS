int main() {
    int i = 0;
    while (i < 3) {
        int j = 0;
        while (j < 2) {
            println_int(i * 10 + j);
            j = j + 1;
        }
        i = i + 1;
    }
    return 0;
}
